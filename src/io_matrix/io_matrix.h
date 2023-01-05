#ifndef __IO_MATRIX_H__
#define __IO_MATRIX_H__


#include "../matrix/matrix.h"
#include <stdio.h>


typedef enum {
    SCAN_MATRIX_SUCCESS = 0,
    INVALID_INPUT_FORMAT = 1
} ScanMatrixExitCode;


void print_matrix(FILE *stream, PMatrix matrix);

ScanMatrixExitCode scan_matrix(FILE *stream, PMatrix *matrix);
/*
    :return:
    SCAN_MATRIX_SUCCESS - считывание матрицы прошло успешно
    INVALID_INPUT_FORMAT - неверный формат входных данных
*/

#endif