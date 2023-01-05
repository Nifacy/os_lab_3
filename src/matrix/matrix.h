#ifndef __MATRIX_H__
#define __MATRIX_H__


#include <complex.h>


typedef double complex MatrixElement;

typedef struct __Matrix *PMatrix;

typedef enum
{
    MATRIX_SUCCESS = 0,
    CREATE_MATRIX_FAILED = 1,
    INVALID_MATRIX_SIZE = 2,
    INVALID_COORDINATES = 3
} MatrixExitCode;


MatrixExitCode create_matrix(int n, int m, PMatrix *matrix);
/*
    Создает матрицу размеров [n x m].

    Возвращаемые значения:
    INVALID_MATRIX_SIZE - ширина или длина матрицы <= 0
    CREATE_MATRIX_FAILED - произошла внутренняя ошибка при создании матрицы
    MATRIX_SUCCESS - матрицы создана успешно
*/


int rows(PMatrix matrix);
/*
    Возвращает количество строк в матрице
*/


int cols(PMatrix matrix);
/*
    Возвращает количество столбцо в матрице
*/


MatrixExitCode get_cell(int i, int j, PMatrix matrix, MatrixElement *out_value);
/*
    Записывает в out_value значение элемента matrix с координатами (i, j)

    Возвращаемые значения:
    INVALID_COORDINATES - номер строки / столбца недействительный: если значение < 0 или превышает размеры матрицы
    MATRIX_SUCCESS - элемент записан успешно
*/


MatrixExitCode set_cell(int i, int j, MatrixElement value, PMatrix matrix);
/*
    Записывает в элемент matrix с координатами (i, j) значение value.

    Возвращаемые значения:
    INVALID_COORDINATES - номер строки / столбца недействительный: если значение < 0 или превышает размеры матрицы
    MATRIX_SUCCESS - значение записано успешно
*/


void delete_matrix(PMatrix matrix);


#endif
