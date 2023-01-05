#include "manager.h"
#include "observer/observer.h"
#include "task_buffer/task_buffer.h"
#include "../worker/worker.h"
#include <stdlib.h>


struct __TaskManager
{
    Worker *workers;
    Observer *observers;
    TaskBuffer buffer;
    int workers_amount;
};


void __init_workers(int amount, Worker **arr)
{
    *arr = (Worker *) calloc(amount, sizeof(Worker));
    for(int i = 0; i < amount; i++) create_worker(&(*arr)[i]);
}


void __init_observers(Worker *workers, int workers_amount, TaskBuffer buffer, Observer **arr)
{
    *arr = (Observer *) calloc(workers_amount, sizeof(Observer));

    for(int i = 0; i < workers_amount; i++)
    {
        create_observer(buffer, workers[i], &(*arr)[i]);
        start_search((*arr)[i]);
    }
}


void create_task_manager(int workers_amount, int buffer_size, TaskManager *manager)
{
    *manager = (TaskManager) malloc(sizeof(struct __TaskManager));
    (*manager)->workers_amount = workers_amount;

    create_task_buffer(
        buffer_size,
        &(*manager)->buffer);
    
    __init_workers(
        workers_amount,
        &(*manager)->workers);
    
    __init_observers(
        (*manager)->workers, workers_amount,
        (*manager)->buffer,
        &(*manager)->observers);
}


void do_task(Task task, TaskManager manager)
{
    add_task(task, manager->buffer);
}


void wait_for_task_complete(TaskManager manager)
{
    while(!is_empty(manager->buffer));

    for(int i = 0; i < manager->workers_amount; i++)
        end_search(manager->observers[i]);

    for(int i = 0; i < manager->workers_amount; i++)
        if(is_busy(manager->workers[i]))
            wait_worker(manager->workers[i]);

    for(int i = 0; i < manager->workers_amount; i++)
        start_search(manager->observers[i]);
}

 
void delete_task_manager(TaskManager manager)
{
    for(int i = 0; i < manager->workers_amount; i++)
    {
        end_search(manager->observers[i]);
        delete_observer(manager->observers[i]);
        delete_worker(manager->workers[i]);
    }

    delete_task_buffer(manager->buffer);

    free(manager->workers);
    free(manager->observers);
    free(manager);
}
