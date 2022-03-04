#ifndef SPARSEMV_H
#define SPARSEMV_H
#include "mesh.h"

int sparsemv(struct mesh *A, const double * const x, double * const y);
#endif
