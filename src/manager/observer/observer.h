#ifndef __OBSERVER_H__
#define __OBSERVER_H__


#include "../task_buffer/task_buffer.h"
#include "../../worker/worker.h"


typedef struct __Observer *Observer;


void create_observer(TaskBuffer buffer, Worker worker, Observer *observer);
void start_search(Observer observer);
void end_search(Observer observer);
void delete_observer(Observer observer);


#endif