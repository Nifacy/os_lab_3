#include "matrix.h"
#include <stdlib.h>
#include <stdio.h>


struct __MatrixSize
{
    int columns;
    int rows;
};


struct __Matrix
{
    struct __MatrixSize size;
    MatrixElement *elements;
};


MatrixExitCode create_matrix(int n, int m, PMatrix *matrix)
{
    if(n <= 0 || m <= 0)
        return INVALID_MATRIX_SIZE;

    *matrix = (PMatrix) malloc(sizeof(struct __Matrix));
    
    if(*matrix == NULL)
        return CREATE_MATRIX_FAILED;
    
    (*matrix)->size.rows = n;
    (*matrix)->size.columns = m;

    (*matrix)->elements = (MatrixElement *) calloc(n * m, sizeof(MatrixElement));
    if((*matrix)->elements == NULL)
    {
        free(*matrix);
        return CREATE_MATRIX_FAILED;
    }

    return MATRIX_SUCCESS;
}


int rows(PMatrix matrix)
{
    return (matrix->size).rows;
}


int cols(PMatrix matrix)
{
    return (matrix->size).columns;
}


MatrixExitCode get_cell(int i, int j, PMatrix matrix, MatrixElement *out_value)
{
    if(i < 0 || i >= rows(matrix) || j < 0 || j >= cols(matrix))
        return INVALID_COORDINATES;

    *out_value = matrix->elements[i * cols(matrix) + j];
    return MATRIX_SUCCESS;
}


MatrixExitCode set_cell(int i, int j, MatrixElement value, PMatrix matrix)
{
    if(i < 0 || i >= rows(matrix) || j < 0 || j >= cols(matrix))
        return INVALID_COORDINATES;

    matrix->elements[i * cols(matrix) + j] = value;
    return MATRIX_SUCCESS;
}


void delete_matrix(PMatrix matrix)
{
    free(matrix->elements);
    free(matrix);
}