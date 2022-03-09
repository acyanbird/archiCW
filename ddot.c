#include "ddot.h"
#include <immintrin.h>
#include <omp.h>

/**
 * @brief Compute the dot product of two vectors
 * 
 * @param n Number of vector elements
 * @param x Input vector
 * @param y Input vector
 * @param result Pointer to scalar result value
 * @return int 0 if no error
 */
int ddot(const int n, const double *const x, const double *const y, double *const result) {
    double local_result = 0.0;
    int i;
    int loopFactor = 4;// 4 double in 256
    int loopN = n / loopFactor * loopFactor;
    __m256d resultVector = _mm256_setzero_pd();
    __m256d xVector, yVector;

        if (y == x) {
            // fmadd = a*b+c
            for (i = 0; i < loopN; i += loopFactor) {
                xVector = _mm256_loadu_pd(x + i);
                xVector = _mm256_mul_pd(xVector, xVector);
                resultVector = _mm256_add_pd(xVector, resultVector);
            }

#pragma omp parallel for simd reduction(+: local_result)
            for (i = loopN; i < n; i++) {
                // wrap up, store to local result
                local_result += x[i] * x[i];
            }

        } else {
            // fmadd = a*b+c
            for (i = 0; i < loopN; i += loopFactor) {
                xVector = _mm256_loadu_pd(x + i);
                yVector = _mm256_loadu_pd(y + i);
                xVector = _mm256_mul_pd(xVector, yVector);
                resultVector = _mm256_add_pd(xVector, resultVector);
            }
#pragma omp parallel for simd reduction(+: local_result)
            for (i = loopN; i < n; i++) {
                // wrap up, store to local result
                local_result += x[i] * y[i];
            }
        }


// r[0] = r[0] + r[1] r[2] = r[2] + r[3]
resultVector = _mm256_hadd_pd(resultVector, resultVector);
// get upper 2, which is sum of original vector
__m128d sumHigh = _mm256_extractf128_pd(resultVector, 1);
// cut lower part of vector
__m128d sum = _mm_add_pd(sumHigh, _mm256_castpd256_pd128(resultVector));
_mm_storel_pd(result, sum);
*result = *result + local_result;

return 0;
}

//int ddot (const int n, const double * const x, const double * const y, double * const result) {
//    double local_result = 0.0;
//    if (y==x){
//        for (int i=0; i<n; i++) {
//            local_result += x[i]*x[i];
//        }
//    } else {
//        for (int i=0; i<n; i++) {
//            local_result += x[i]*y[i];
//        }
//    }
//    *result = local_result;
//
//    return 0;
//}
