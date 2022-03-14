#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include <immintrin.h>
#include <omp.h>

#include "sparsemv.h"

/**
 * @brief Compute matrix vector product (y = A*x)
 * 
 * @param A Known matrix
 * @param x Known vector
 * @param y Return vector
 * @return int 0 if no error
 */

//int sparsemv(struct mesh *A, const double *const x, double *const y) {
//
//    const int nrow = (const int) A->local_nrow;
//
//    for (int i = 0; i < nrow; i++) {
//        double sum = 0.0;
//        const double *const cur_vals = (const double *const) A->ptr_to_vals_in_row[i];
//        const int *const cur_inds = (const int *const) A->ptr_to_inds_in_row[i];
//        const int cur_nnz = (const int) A->nnz_in_row[i];
//
//        // init vector
//        __m256d xV, cur_valsV;
//        __m256d sumV = _mm256_setzero_pd();
//
//        int loopFactor = 4;
//        int loopN = cur_nnz / loopFactor * loopFactor;
//        int j;
//
//        for (j = 0; j < loopN ; j += loopFactor) {
//            xV = _mm256_set_pd(x[cur_inds[j]], x[cur_inds[j + 1]], x[cur_inds[j + 2]], x[cur_inds[j + 3]]);
//            cur_valsV = _mm256_loadu_pd(cur_vals + j);
//            sumV = _mm256_add_pd(sumV, _mm256_mul_pd(xV, cur_valsV));
//        }
//            // wrap up
//        for (; j < cur_nnz; j++) {
//            sum += cur_vals[j] * x[cur_inds[j]];
//        }
//        sumV = _mm256_hadd_pd(sumV, sumV);
//        // get upper 2, which is sum of original vector
//        __m128d sumHigh = _mm256_extractf128_pd(sumV, 1);
//        // cut lower part of vector
//        __m128d finalSum = _mm_add_pd(sumHigh, _mm256_castpd256_pd128(sumV));
//        _mm_storel_pd(y + i, finalSum);
//        y[i] = y[i] + sum;
////        y[i] = sum;
//    }
//    return 0;
//}


int sparsemv(struct mesh *A, const double * const x, double * const y)
{

  const int nrow = (const int) A->local_nrow;

  for (int i=0; i< nrow; i++) {
      double sum = 0.0;
      const double * const cur_vals = (const double * const) A->ptr_to_vals_in_row[i];
      const int * const cur_inds = (const int * const) A->ptr_to_inds_in_row[i];
      const int cur_nnz = (const int) A->nnz_in_row[i];
      int j;

//      int loopFactor = 4;
//      int loopN = cur_nnz / loopFactor * loopFactor;

//#pragma omp parallel for simd schedule(auto) reduction(+:sum)
      for (j = 0; j < cur_nnz; j ++) {
          sum += cur_vals[j] * x[cur_inds[j]];
//          sum += cur_vals[j + 1] * x[cur_inds[j + 1]];
//          sum += cur_vals[j + 2] * x[cur_inds[j + 2]];
//          sum += cur_vals[j + 3] * x[cur_inds[j + 3]];
      }

//      for (; j < cur_nnz; j++) {
//          sum += cur_vals[j] * x[cur_inds[j]];
//      }

      y[i] = sum;
    }
  return 0;
}
