#ifndef __WORKER_H__
#define __WORKER_H__

#include "../task/task.h"
#include <stdbool.h>

typedef struct __Worker *Worker;

void create_worker(Worker *worker);
void run_task(Task task, Worker worker);
void wait_worker(Worker worker);
void delete_worker(Worker worker);
bool is_busy(Worker worker);

#endif