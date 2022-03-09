#include "waxpby.h"
#include <immintrin.h>

/**
 * @brief Compute the update of a vector with the sum of two scaled vectors
 * 
 * @param n Number of vector elements
 * @param alpha Scalars applied to x
 * @param x Input vector
 * @param beta Scalars applied to y
 * @param y Input vector
 * @param w Output vector
 * @return int 0 if no error
 */


int waxpby(const int n, const double alpha, const double *const x, const double beta, const double *const y, double *const w) {
    // init for constant alpha and beta
    __m256d alphaV = _mm256_set1_pd(alpha);
    __m256d betaV = _mm256_set1_pd(beta);

    // init vector
    __m256d xVector, yVector;

    // 4 double per 256 bits
    int loopFactor = 4;
    int loopN = n / loopFactor * loopFactor;
    int i;

#pragma omp parallel private(xVector, yVector) shared(alphaV, betaV)
    {
        if (alpha == 1.0) {
#pragma omp for schedule(auto)
            for (i = 0; i < loopN; i += loopFactor) {
                xVector = _mm256_loadu_pd(x + i);
                yVector = _mm256_loadu_pd(y + i);
                yVector = _mm256_mul_pd(betaV, yVector);
                _mm256_storeu_pd(w + i, _mm256_add_pd(xVector, yVector));
            }
#pragma omp for schedule(auto)
            for (i = loopN; i < n; i++) {
                w[i] = x[i] + beta * y[i];
            }
        } else if (beta == 1.0) {
#pragma omp for schedule(auto)
            for (i = 0; i < loopN; i += loopFactor) {
                xVector = _mm256_loadu_pd(x + i);
                yVector = _mm256_loadu_pd(y + i);
                xVector = _mm256_mul_pd(alphaV, xVector);
                _mm256_storeu_pd(w + i, _mm256_add_pd(xVector, yVector));
            }
#pragma omp for schedule(auto)
            for (i = loopN ; i < n; i++) {
                w[i] = alpha * x[i] + y[i];
            }
        } else {
#pragma omp for schedule(auto)
            for (i = 0; i < loopN; i += loopFactor) {
                xVector = _mm256_loadu_pd(x + i);
                yVector = _mm256_loadu_pd(y + i);
                xVector = _mm256_mul_pd(alphaV, xVector);
                yVector = _mm256_mul_pd(betaV, yVector);
                _mm256_storeu_pd(w + i, _mm256_add_pd(xVector, yVector));
            }
#pragma omp for schedule(auto)
            for (i = loopN; i < n; i++) {
                w[i] = alpha * x[i] + beta * y[i];
            }
        }
    }

    return 0;
}

//int waxpby (const int n, const double alpha, const double * const x, const double beta, const double * const y, double * const w) {
//    if (alpha==1.0) {
//        for (int i=0; i<n; i++) {
//            w[i] = x[i] + beta * y[i];
//        }
//    } else if(beta==1.0) {
//        for (int i=0; i<n; i++) {
//            w[i] = alpha * x[i] + y[i];
//        }
//    } else {
//        for (int i=0; i<n; i++) {
//            w[i] = alpha * x[i] + beta * y[i];
//        }
//    }
//
//    return 0;
//}
