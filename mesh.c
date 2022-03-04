#include "HPC_Sparse_Matrix.h"

/**
 * @brief Clean up the matrix, freeing all memory
 * 
 * @param A Matrix to be cleaned up
 */
void destroyMatrix(struct mesh *A)
{
  if (A->nnz_in_row) {
    free(A->nnz_in_row);
  }
  if (A->list_of_vals) {
    free(A->list_of_vals);
  }
  if (A->ptr_to_vals_in_row != 0) {
    free(A->ptr_to_vals_in_row);
  }
  if (A->list_of_inds) {
    free(A->list_of_inds);
  }
  if (A->ptr_to_inds_in_row != 0) {
    free(A->ptr_to_inds_in_row);
  }
  if (A->ptr_to_diags) {
    free(A->ptr_to_diags);
  }

  free(A);
  A = 0;
}
