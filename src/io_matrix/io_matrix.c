#include "io_matrix.h"


void print_matrix(FILE *stream, PMatrix matrix) {
	for (int i = 0; i < rows(matrix); i++) {
		for (int j = 0; j < cols(matrix); j++) {
			  MatrixElement el;
			  get_cell(i, j, matrix, &el);
			  fprintf(stream, "%.2f + %.2fi\t", creal(el), cimag(el));
		}
		fprintf(stream, "\n");
	}
}


ScanMatrixExitCode scan_matrix(FILE *stream, PMatrix *matrix)
{
	int rows, cols;
	float real, imag;

	if(fscanf(stream, "%d %d", &rows, &cols) != 2)
        return INVALID_INPUT_FORMAT;

	create_matrix(rows, cols, matrix);

	for(int i = 0; i < rows; i++)
	{
		for(int j = 0; j < cols; j++)
		{	
            if(fscanf(stream, "%f + %fi", &real, &imag) != 2)
                return INVALID_INPUT_FORMAT;
            
			set_cell(i, j, CMPLX(real, imag), *matrix);
		}
	}

	return SCAN_MATRIX_SUCCESS;
}
