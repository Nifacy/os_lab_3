#ifndef __TASK_H__
#define __TASK_H__


#include "../matrix/matrix.h"


typedef struct {
  PMatrix a, b;
  int i, j;
  PMatrix out_matrix;
} Task;


#endif