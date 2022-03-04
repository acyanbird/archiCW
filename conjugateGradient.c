#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "mytimer.h"
#include "conjugateGradient.h"

#ifdef USING_SILO
#include "silo_writer.h"
#endif

/* Key definitions for calculating the time spend on a particular section */
#define TICK() t0 = mytimer()
#define TOCK(t) t += mytimer() - t0

/**
 * @brief Routine to compute an approximate solution to Ax = b
 * 
 * @param A Known matrix stored as an mesh struct (known matrix)
 * @param b Known right hand side vector (known vector, constant)
 * @param x On entry is initial guess, on exit new approximate solution (unknown vector)
 * @param max_iter Maximum number of iterations to perform, even if tolerance is not met.
 * @param tolerance Stop and assert convergence if norm of residual is to tolerance.
 * @param niters On output, the number of iterations actually performed.
 * @param normr Stores the residual
 * @param times Array of kernel times, to be printed once finished 
 * @param siloName Name used for the Silo files (if Silo is in use)
 * @return int 0 if no error.
 */
int conjugateGradient(struct mesh *A,
          const double *const b, double *const x,
          const int max_iter, const double tolerance, int *niters, double *normr,
          double *times, char* siloName
#ifndef USING_SILO
 __attribute__((unused))
#endif
          )

{
  /* Set up and start timers */
  double t_begin = mytimer(); // Start timing right away
  double t0 = 0.0, t1 = 0.0, t2 = 0.0, t3 = 0.0;

  /* Create key variables */
  int nrow = A->local_nrow;
  int ncol = A->local_ncol;

  double *r = (double *) malloc(sizeof(double) * nrow);
  double *p = (double *) malloc(sizeof(double) * ncol); // In parallel case, A is rectangular
  double *Ap = (double *) malloc(sizeof(double) * nrow);

  *normr = 0.0;
  double rtrans = 0.0;
  double oldrtrans = 0.0;

  int k = 0;

  /* Setup initial timestep */
  // p is of length ncols, copy x to p for sparse MV operation
  TICK();
  waxpby(nrow, 1.0, x, 0.0, x, p);
  TOCK(t2);
  TICK();
  sparsemv(A, p, Ap);
  TOCK(t3);
  TICK();
  waxpby(nrow, 1.0, b, -1.0, Ap, r);
  TOCK(t2);
  TICK();
  ddot(nrow, r, r, &rtrans);
  TOCK(t1);
  *normr = sqrt(rtrans);

  /* Write SILO file */
#ifdef USING_SILO
  int err = writeTimestep(siloName, &k, A, p, r, Ap, b, x);
  if (err != 0) {return err;}
#endif

#ifdef USING_VERBOSE
  int print_freq = 1;
  printf("Initial Residual = %e\n", *normr);
#endif

  /* Calculate each iteration until the max number of iterations is done, or the residual is bellow the tolerance */
  for (k = 1; k < max_iter && *normr > tolerance; k++)
  {
    if (k == 1) {
      TICK();
      waxpby(nrow, 1.0, r, 0.0, r, p);
      TOCK(t2);
    } else {
      oldrtrans = rtrans;
      TICK();
      ddot(nrow, r, r, &rtrans);
      TOCK(t1); // 2*nrow ops
      double beta = rtrans / oldrtrans;
      TICK();
      waxpby(nrow, 1.0, r, beta, p, p);
      TOCK(t2); // 2*nrow ops
    }

    *normr = sqrt(rtrans);
#ifdef USING_VERBOSE  
    if (k % print_freq == 0 || k + 1 == max_iter) {
      printf("Iteration = %.4d \t Residual = %e\n", k, *normr);
    }
#endif

    TICK();
    sparsemv(A, p, Ap);
    TOCK(t3); // 2*nnz ops
    double alpha = 0.0;
    TICK();
    ddot(nrow, p, Ap, &alpha);
    TOCK(t1); // 2*nrow ops
    alpha = rtrans / alpha;
    TICK();
    waxpby(nrow, 1.0, x, alpha, p, x); // 2*nrow ops
    waxpby(nrow, 1.0, r, -alpha, Ap, r);
    TOCK(t2); // 2*nrow ops
    *niters = k;

    /* Write SILO file */
#ifdef USING_SILO
    int err = writeTimestep(siloName, &k, A, p, r, Ap, b, x);
    if (err != 0) {
      return err;
    }
#endif
  }

  /* Store times */
  times[1] = t1; // ddot time
  times[2] = t2; // waxpby time
  times[3] = t3; // sparsemv time

  /* Cleanup created arrays */
  free(p);
  free(Ap);
  free(r);

  /* Calculate total time spent */
  times[0] = mytimer() - t_begin;

  /* Thats all folks! */
  return (0);
}
