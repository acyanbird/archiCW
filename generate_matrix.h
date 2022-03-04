#ifndef GENERATE_MATRIX_H
#define GENERATE_MATRIX_H

#include "mesh.h"

void generate_matrix(int nx, int ny, int nz, struct mesh **A, double **x, double **b, double **xexact, int use_7pt_stencil);
#endif
