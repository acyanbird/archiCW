#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#include "sparsemv.h"

/**
 * @brief Compute matrix vector product (y = A*x)
 * 
 * @param A Known matrix
 * @param x Known vector
 * @param y Return vector
 * @return int 0 if no error
 */
int sparsemv(struct mesh *A, const double * const x, double * const y)
{

  const int nrow = (const int) A->local_nrow;

  for (int i=0; i< nrow; i++) {
      double sum = 0.0;
      const double * const cur_vals = (const double * const) A->ptr_to_vals_in_row[i];
      const int * const cur_inds = (const int * const) A->ptr_to_inds_in_row[i];
      const int cur_nnz = (const int) A->nnz_in_row[i];

      for (int j=0; j< cur_nnz; j++) {
        sum += cur_vals[j]*x[cur_inds[j]];
      }
      y[i] = sum;
    }
  return 0;
}
