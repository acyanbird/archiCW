#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "generate_matrix.h"

/**
 * @brief Generates the inital mesh and values
 * 
 * @param nx Size of x dimension
 * @param ny Size of y dimension
 * @param nz Size of z dimension
 * @param A Sparse matrix
 * @param x Inital guess for the mesh
 * @param b Right hand side
 * @param xexact Exact solution (as computed by a direct solver)
 * @param use_7pt_stencil true if using 7 point stencil, otherwise use 27 point stencil
 */
void generate_matrix(int nx, int ny, int nz, struct mesh **A, double **x, double **b, double **xexact, int use_7pt_stencil)
{
  *A = (struct mesh *) malloc(sizeof(struct mesh)); // Allocate matrix struct and fill it

  int local_nrow = nx * ny * nz;   // This is the size of our subblock
  if (local_nrow <= 0) {
    exit(3);
  }          // Must have something to work with
  int local_nnz = 27 * local_nrow; // Approximately 27 nonzeros per row (except for boundary nodes)

  int total_nrow = local_nrow;               // Total number of grid points in mesh
  long long total_nnz = 27 * (long long)total_nrow; // Approximately 27 nonzeros per row (except for boundary nodes)

  int start_row = 0; // Each processor gets a section of a chimney stack domain
  int stop_row = start_row + local_nrow - 1;

  // Allocate arrays that are of length local_nrow
  (*A)->nnz_in_row = (int *) malloc(sizeof(int) * local_nrow);
  (*A)->ptr_to_vals_in_row = (double **) malloc(sizeof(double *) * local_nrow);
  (*A)->ptr_to_inds_in_row = (int **) malloc(sizeof(int *) * local_nrow);
  (*A)->ptr_to_diags = (double **) malloc(sizeof(double *) * local_nrow);

  *x = (double *) malloc(sizeof(double) * local_nrow);
  *b = (double *) malloc(sizeof(double) * local_nrow);
  *xexact = (double *) malloc(sizeof(double) * local_nrow);

  // Allocate arrays that are of length local_nnz
  (*A)->list_of_vals = (double *) malloc(sizeof(double) * local_nnz);
  (*A)->list_of_inds = (int *) malloc(sizeof(int) * local_nnz);

  double *curvalptr = (*A)->list_of_vals;
  int *curindptr = (*A)->list_of_inds;

  long long nnzglobal = 0;
  for (int iz = 0; iz < nz; iz++) {
    for (int iy = 0; iy < ny; iy++) {
      for (int ix = 0; ix < nx; ix++) {
        int currow = iz * nx * ny + iy * nx + ix;
        int nnzrow = 0;
        (*A)->ptr_to_vals_in_row[currow] = curvalptr;
        (*A)->ptr_to_inds_in_row[currow] = curindptr;
        for (int sz = -1; sz <= 1; sz++) {
          for (int sy = -1; sy <= 1; sy++) {
            for (int sx = -1; sx <= 1; sx++) {
              int curcol = currow + sz * nx * ny + sy * nx + sx;
              //            Since we have a stack of nx by ny by nz domains , stacking in the z direction, we check to see
              //            if sx and sy are reaching outside of the domain, while the check for the curcol being valid
              //            is sufficient to check the z values
              if ((ix + sx >= 0) && (ix + sx < nx) && (iy + sy >= 0) && (iy + sy < ny) && (curcol >= 0 && curcol < total_nrow)) {
                if (!use_7pt_stencil || (sz * sz + sy * sy + sx * sx <= 1)) { // This logic will skip over point that are not part of a 7-pt stencil
                  if (curcol == currow) {
                    (*A)->ptr_to_diags[currow] = curvalptr;
                    *curvalptr++ = 27.0;
                  } else {
                    *curvalptr++ = -1.0;
                  }
                  *curindptr++ = curcol;
                  nnzrow++;
                }
              }
            }
          }
        }
        (*A)->nnz_in_row[currow] = nnzrow;
        nnzglobal += nnzrow;
        (*x)[currow] = 0.0;
        (*b)[currow] = 27.0 - ((double)(nnzrow - 1));
        (*xexact)[currow] = 1.0;
      }
    }
  }

  (*A)->start_row = start_row;
  (*A)->stop_row = stop_row;
  (*A)->total_nrow = total_nrow;
  (*A)->total_nnz = total_nnz;
  (*A)->local_nrow = local_nrow;
  (*A)->local_ncol = local_nrow;
  (*A)->local_nnz = local_nnz;
  (*A)->size_x = nx;
  (*A)->size_y = ny;
  (*A)->size_z = nz;

  return;
}
