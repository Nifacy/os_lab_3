#include "matrix/matrix.h"
#include "io_matrix/io_matrix.h"
#include "manager/manager.h"
#include "task/task.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int workers_amount;
int buffer_size;

void handle_scan_error(ScanMatrixExitCode code)
{
	if(code == INVALID_INPUT_FORMAT)
		perror("[ScanMatrixError] Invalid input data format!\n");

	exit(20 + code);
}


PMatrix multiply(PMatrix a, PMatrix b) {
	if (cols(a) != rows(b)) {
		perror("[MultiplyError] Invalid matrix sizes\n");
		exit(31);
	}

	PMatrix c;
	TaskManager manager;

	create_matrix(rows(a), cols(b), &c);
	create_task_manager(workers_amount, buffer_size, &manager);

	for(int i = 0; i < rows(c); i++)
	{
		for(int j = 0; j < cols(c); j++)
		{
			Task task = {a, b, i, j, c};
			do_task(task, manager);
		}
	}

	wait_for_task_complete(manager);
	delete_task_manager(manager);
	return c;
}


int main(int argc, char *argv[]) {
	PMatrix a, b, c;
	int scan_result;

	workers_amount = (argc >= 2) ? atoi(argv[1]) : 1;
	buffer_size = (argc >= 3) ? atoi(argv[2]) : 1;

	scan_result = scan_matrix(stdin, &a);
	if(scan_result != SCAN_MATRIX_SUCCESS)
		handle_scan_error(scan_result);

	scan_result = scan_matrix(stdin, &b);
	if(scan_result != SCAN_MATRIX_SUCCESS)
		handle_scan_error(scan_result);

	c = multiply(a, b);
	print_matrix(stdout, c);

	delete_matrix(a);
	delete_matrix(b);
	delete_matrix(c);

	return 0;
}
