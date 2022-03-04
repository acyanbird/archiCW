#ifndef MESH_H
#define MESH_H

/**
 * @brief Stores key information about the matrix
 * 
 */
struct mesh
{
  int start_row;
  int stop_row;
  int total_nrow;
  long long total_nnz;
  int local_nrow;
  int local_ncol; // Must be defined in make_local_matrix
  int local_nnz;
  int size_x; //Size of mesh in x dimension
  int size_y; //Size of mesh in y dimension
  int size_z; //Size of mesh in z dimension
  int *nnz_in_row;
  double **ptr_to_vals_in_row;
  int **ptr_to_inds_in_row;
  double **ptr_to_diags;

  double *list_of_vals; //needed for cleaning up memory
  int *list_of_inds;    //needed for cleaning up memory
};

void destroyMatrix(struct mesh *A);

#endif
