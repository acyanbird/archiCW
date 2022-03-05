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
    __m256d xVector;
    __m256d yVector;

    // 4 double per 256 bits
    int loopFactor = 4;
    int loopN = n / loopFactor * loopFactor;
    int i;

    if (alpha == 1.0) {
        for (i = 0; i < loopN; i += loopFactor) {
            xVector = _mm256_load_pd(x + i);
            yVector = _mm256_load_pd(y + i);
            yVector = _mm256_mul_pd(betaV, yVector);
            _mm256_store_pd(w + i, _mm256_add_pd(xVector, yVector));
        }
        for (; i < n; i++) {
            w[i] = x[i] + beta * y[i];
        }
    } else if (beta == 1.0) {
        for (i = 0; i < loopN; i += loopFactor) {
            xVector = _mm256_load_pd(x + i);
            yVector = _mm256_load_pd(y + i);
            xVector = _mm256_mul_pd(alphaV, xVector);
            _mm256_store_pd(w + i, _mm256_add_pd(xVector, yVector));
        }
        for (; i < n; i++) {
            w[i] = alpha * x[i] + y[i];
        }
    } else {
        for (i = 0; i < loopN; i += loopFactor) {
            xVector = _mm256_load_pd(x + i);
            yVector = _mm256_load_pd(y + i);
            xVector = _mm256_mul_pd(alphaV, xVector);
            yVector = _mm256_mul_pd(betaV, yVector);
            _mm256_store_pd(w + i, _mm256_add_pd(xVector, yVector));
        }
        for (; i < n; i++) {
            w[i] = alpha * x[i] + beta * y[i];
        }
    }

    return 0;
}
