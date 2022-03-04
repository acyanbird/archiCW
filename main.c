#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include "generate_matrix.h"
#include "mytimer.h"
#include "sparsemv.h"
#include "compute_residual.h"
#include "conjugateGradient.h"
#include "mesh.h"

/**
 * @brief Main entry point to the program
 * 
 * The program consists of 3 sections.
 * The first section is the initialisation stage, which includes setting up key values, checking the parameters passed in are correct, and generating the resulting matrix. This is not timed. 
 * The second section is the computation phase. The time taken is calculated within the function, with pointers used to pass the results back.
 * The third and final section is the printing of the output, and the cleanup of any variables. This is not timed.
 * 
 * @param argc Number of arguments passed to the program (including the name of the program)
 * @param argv Array of each parameter passed
 * @return int 0 if no error
 */
int main(int argc, char *argv[])
{
  /* Initalise values and matrix */
  struct mesh *A;
  double *x, *b, *xexact;
  int ierr = 0;
  double times[4];
  int nx, ny, nz;
  int stencil_bool = 0;

  /* Create file and dir (and if using Silo, the Silo) name */
  time_t rawtime;
  time(&rawtime);
  struct tm * ptm = localtime(&rawtime);
  char fileName[25];
  sprintf(fileName,"%04d_%02d_%02d_%02d_%02d_%02d",ptm->tm_year + 1900, ptm->tm_mon+1,
    ptm->tm_mday, ptm->tm_hour, ptm->tm_min,ptm->tm_sec);

  if (argc < 4) {
    fprintf(stderr, "Usage:\n\t%s nx ny nz\n\t\twhere nx, ny and nz are the local sub-block dimensions\n\t%s nx ny nz 7pt-stencil\n\t\twhere nx, ny and nz are the local sub-block dimensions and 7pt-stencil is a boolean stating whether to use 7pt-stencil (default is 0 (false), 1 is true)\n", argv[0], argv[0]);
    exit(1);
  } else { 
    nx = atoi(argv[1]);
    ny = atoi(argv[2]);
    nz = atoi(argv[3]);
    if (argc > 4 && atoi(argv[4]) == 1) {
      stencil_bool = 1;
    }
    generate_matrix(nx, ny, nz, &A, &x, &b, &xexact, stencil_bool);
  }

  /* Computation */
  int niters = 0;
  double normr = 0.0;
  int max_iter = 150;
  double tolerance = 0.0; // Set tolerance to zero to make all runs do max_iter iterations
#ifdef USING_SILO
  ierr = conjugateGradient(A, b, x, max_iter, tolerance, &niters, &normr, times, fileName);
#else
  ierr = conjugateGradient(A, b, x, max_iter, tolerance, &niters, &normr, times, "");
#endif

  if (ierr)
    fprintf(stderr, "Error in call to CG: %d .\n", ierr);

  /* Generate final stats (print and if possible, save to file) */
  double fniters = niters;
  double fnrow = A->total_nrow;
  double fnnz = A->total_nnz;
  double fnops_ddot = fniters * 4 * fnrow;
  double fnops_waxpby = fniters * 6 * fnrow;
  double fnops_sparsemv = fniters * 2 * fnnz;
  double fnops = fnops_ddot + fnops_waxpby + fnops_sparsemv;


  char finalStats[1000] = "\n===== Final Statistics =====\n";
  char tmpString[100];
  sprintf(tmpString, "Executable name:      %s\n", argv[0]);
  strcat(finalStats, tmpString);
  sprintf(tmpString, "Dimensions:           %d %d %d\n", nx, ny, nz);
  strcat(finalStats, tmpString);
  sprintf(tmpString, "Number of iterations: %d\n", niters);
  strcat(finalStats, tmpString);
  sprintf(tmpString, "Final residual:       %e\n\n", normr);
  strcat(finalStats, tmpString);
  sprintf(tmpString, "=== Time ==\nTotal:           %e seconds\n", times[0]);
  strcat(finalStats, tmpString);
  sprintf(tmpString, "ddot Kernel:     %e seconds\n", times[1]);
  strcat(finalStats, tmpString);
  sprintf(tmpString, "waxpby Kernel:   %e seconds\n", times[2]);
  strcat(finalStats, tmpString);
  sprintf(tmpString, "sparsemv Kernel: %e seconds\n\n", times[3]);
  strcat(finalStats, tmpString);
  sprintf(tmpString, "=== FLOP ==\nTotal:           %e floating point operations\n", fnops);
  strcat(finalStats, tmpString);
  sprintf(tmpString, "ddot Kernel:     %e floating point operations\n", fnops_ddot);
  strcat(finalStats, tmpString);
  sprintf(tmpString, "waxpby Kernel:   %e floating point operations\n", fnops_waxpby);
  strcat(finalStats, tmpString);
  sprintf(tmpString, "sparsemv Kernel: %e floating point operations\n\n", fnops_sparsemv);
  strcat(finalStats, tmpString);
  sprintf(tmpString, "=== MFLOP/s ==\nTotal:           %e MFLOP/s\n", fnops / times[0] / 1.0E6);
  strcat(finalStats, tmpString);
  sprintf(tmpString, "ddot Kernel:     %e MFLOP/s\n", fnops_ddot / times[1] / 1.0E6);
  strcat(finalStats, tmpString);
  sprintf(tmpString, "waxpby Kernel:   %e MFLOP/s\n", fnops_waxpby / times[2] / 1.0E6);
  strcat(finalStats, tmpString);
  sprintf(tmpString, "sparsemv Kernel: %e MFLOP/s\n\n", fnops_sparsemv / (times[3]) / 1.0E6);
  strcat(finalStats, tmpString);

  /* Compute difference between known exact solution and computed solution */
  double residual = 0;
  if ((ierr = compute_residual(A->local_nrow, x, xexact, &residual))) {
    fprintf(stderr,"Error in call to compute_residual: %d \n", ierr);
  }

  sprintf(tmpString, "Difference between computed and exact = %e \n", residual);
  strcat(finalStats, tmpString);

  /* Print out final stats */
  printf("%s", finalStats);

  /* Generate final stats file */
  FILE *fptr;
  char * fileOutputName = (char * ) malloc(sizeof(char)*(strlen(fileName) + 5));
  sprintf(fileOutputName, "%s.txt", fileName);
  fptr = fopen(fileOutputName, "w");
  if (fptr == NULL) {
    fprintf(stderr, "Output file cannot be generated, skipping");
  } else {
    fprintf(fptr, "%s", finalStats);
    fclose(fptr);
  }
  free(fileOutputName);

  /* Thats all folks...! */
  return 0;
} 
