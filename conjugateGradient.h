#ifndef HPCCG_H
#define HPCCG_H
#include <string.h>

#include "sparsemv.h"
#include "ddot.h"
#include "waxpby.h"
#include "mesh.h"

int conjugateGradient(struct mesh * A,
	  const double * const b, double * const x,
	  const int max_iter, const double tolerance, int *niters, double *normr, double * times,
	  char* siloName);
#endif
