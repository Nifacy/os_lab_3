#ifndef __TASK_MANAGER_H__
#define __TASK_MANAGER_H__


#include "../task/task.h"


typedef struct __TaskManager *TaskManager;


void create_task_manager(int workers_amount, int buffer_size, TaskManager *manager);
void do_task(Task task, TaskManager manager);
void wait_for_task_complete(TaskManager manager);
void delete_task_manager(TaskManager manager);

#endif