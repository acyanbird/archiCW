#include "waxpby.h"
//#include <mmintrin.h>   //mmx, 4个64位寄存器
//#include <xmmintrin.h>  //sse, 8个128位寄存器
//#include <emmintrin.h>  //sse2, 8个128位寄存器
//#include <pmmintrin.h>  //sse3, 8个128位寄存器
//#include <smmintrin.h>  //sse4.1, 8个128位寄存器
//#include <nmmintrin.h>  //sse4.2, 8个128位寄存器
#include <immintrin.h>  // avx, 16个256位寄存器

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


int waxpby (const int n, const double alpha, const double * const x, const double beta, const double * const y, double * const w) {  
  if (alpha==1.0) {
    for (int i=0; i<n; i++) {
      w[i] = x[i] + beta * y[i];
    }
  } else if(beta==1.0) {
    for (int i=0; i<n; i++) {
      w[i] = alpha * x[i] + y[i];
    }
  } else {
    for (int i=0; i<n; i++) {
      w[i] = alpha * x[i] + beta * y[i];
    }
  }

  return 0;
}
