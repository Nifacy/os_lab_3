#ifndef __TASK_BUFFER_H__
#define __TASK_BUFFER_H__


#include "../../task/task.h"
#include <stdbool.h>


typedef struct __TaskBuffer *TaskBuffer;


void create_task_buffer(int buffer_size, TaskBuffer *buffer);
void add_task(Task task, TaskBuffer buffer);
Task get_task(TaskBuffer buffer);
void delete_task_buffer(TaskBuffer buffer);
bool is_empty(TaskBuffer buffer);

#endif