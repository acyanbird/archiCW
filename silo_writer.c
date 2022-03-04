#include "silo_writer.h"

#include <stdio.h>

/**
 * @brief Produces Silo files for a collection of variables, within a given directory
 * 
 * @param dir Directory the file should be stored
 * @param timestep Timestep the file was created in
 * @param matrix The matrix data
 * @param p Current working vector
 * @param r Used as part of residual calculations (currently unused)
 * @param Ap Temporary matrix data (currently unused)
 * @param b Right hand side vector (currently unused)
 * @param x Current state of the solution
 * @return int 0 if no error
 */
int writeTimestep(char* dir, int *timestep, struct mesh* matrix, double* p, double* r __attribute__((unused)), double* Ap __attribute__((unused)), const double *const b __attribute__((unused)), double *const x) {
    char* filename;

    /* Check dir has been created, create if not */
    struct stat st;
    if (stat(dir, &st) != 0) {
        mkdir(dir, 0700);
    }

    /* Create filename */
    int filenameSize = strlen(dir) + 16;
    filename = (char*) malloc(sizeof(char) * filenameSize);
    sprintf(filename, "%s/output%04d.silo", dir, *timestep);

    DBfile *dbfile = NULL;
    /* Open the Silo file */
    dbfile = DBCreate(filename, DB_CLOBBER, DB_LOCAL, "HPCCG timestep",  DB_PDB);
    if(dbfile == NULL) {
        fprintf(stderr, "Could not create Silo file!\n");
        free(filename);
        return -1;
    }
    
    /* Add database options */
    DBoptlist *optlist = DBMakeOptlist(1);
    DBAddOption(optlist, DBOPT_CYCLE, timestep);

    /* Write mesh */
    int ndims = 3;
    int dims[] = {matrix->size_x, matrix->size_y, matrix->size_z};

    /* Set x coordinates */
    double * xArray = (double *) malloc(matrix->size_x*sizeof(double));
    for (int i = 0; i < matrix->size_x; i++) {
        xArray[i] = i;
    }

    /* Set y coordinates */
    double * yArray = (double *) malloc(matrix->size_y*sizeof(double));
    for (int i = 0; i < matrix->size_y; i++) {
        yArray[i] = i;
    }

    /* Set z coordinates */
    double * zArray = (double *) malloc(matrix->size_z*sizeof(double));
    for (int i = 0; i < matrix->size_z; i++) {
        zArray[i] = i;
    }

    /* Create coordinates array */
    double *coords[] = {xArray, yArray, zArray};

    /* Generate mesh */
    DBPutQuadmesh(dbfile, "quadmesh", NULL, coords, dims, ndims, DB_DOUBLE, DB_COLLINEAR, optlist);

    /* Add variables */
    DBPutQuadvar1(dbfile, "p_nodal", "quadmesh", p, dims, ndims, NULL, 0, DB_DOUBLE, DB_NODECENT, optlist);
//    DBPutQuadvar1(dbfile, "r_nodal", "quadmesh", r, dims, ndims, NULL, 0, DB_DOUBLE, DB_NODECENT, optlist);
//    DBPutQuadvar1(dbfile, "Ap_nodal", "quadmesh", Ap, dims, ndims, NULL, 0, DB_DOUBLE, DB_NODECENT, optlist);
//    DBPutQuadvar1(dbfile, "b_nodal", "quadmesh", b, dims, ndims, NULL, 0, DB_DOUBLE, DB_NODECENT, optlist);
    DBPutQuadvar1(dbfile, "x_nodal", "quadmesh", x, dims, ndims, NULL, 0, DB_DOUBLE, DB_NODECENT, optlist);

    /* Close and free everything. */
    DBFreeOptlist(optlist);
    DBClose(dbfile);
    free(filename);
    free(xArray);
    free(yArray);
    free(zArray);
    return 0;
}