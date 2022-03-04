#ifndef SILO_WRITER_H
#define SILO_WRITER_H

#include <silo.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include "mesh.h"

int writeTimestep(char* dir, int *timestep, struct mesh * matrix, double* p, double* r, double* Ap, const double *const b, double *const x);

#endif