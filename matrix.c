#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "VerticesGroup.h"
#include "defs.h"
#include "ErrorHandler.h"
#include <math.h>

void printVect(double *vector, int length);

/**
 * Generate a square matrix object
 * @param n size of matrix is nxn
 * @return matrix
 */
Matrix *createMatrix(int n) {
    int i;
    Matrix *mat = malloc(sizeof(Matrix));
    assertMemoryAllocation(mat);
    mat->n = n;
    mat->values = malloc(sizeof(double *) * n);
    assertMemoryAllocation(mat->values);
    for (i = 0; i < n; i++) {
        mat->values[i] = calloc(n, sizeof(double));
        assertMemoryAllocation(mat->values[i]);
    }
    return mat;
}

/**
 * Free all the memory allocated by a matrix
 * @param mat matrix object
 */
void freeMatrix(Matrix *mat) {
    int i;
    for (i = 0; i < mat->n; i++) {
        free(mat->values[i]);
    }
    free(mat->values);
    free(mat);
}

/**
 * Set value in matrix
 * @param mat
 * @param r row
 * @param c column
 * @return value
 */
void setVal(Matrix *mat, int r, int c, double val) {
    mat->values[r][c] = val;
}

/**
 * Read value in matrix
 * @param mat
 * @param r row
 * @param c column
 * @return value
 */
double readVal(Matrix *mat, int r, int c) {
    return mat->values[r][c];
}

