#include "observer.h"
#include <pthread.h>
#include <stdlib.h>


struct __Observer
{
    TaskBuffer observed_buffer;
    Worker worker;
    pthread_t observer_thread_id;

    pthread_mutex_t end_search_lock;
};


void __observer_thread_code(Observer observer)
{
    while(1)
    {
        Task task = get_task(observer->observed_buffer);

        pthread_mutex_lock(&(observer->end_search_lock));
            run_task(task, observer->worker);
        pthread_mutex_unlock(&(observer->end_search_lock));
        
        wait_worker(observer->worker);
    }
}


void *__observer_thread_code_wrapper(void *data)
{
    Observer observer = (Observer) data;
    __observer_thread_code(observer);
    pthread_exit(0);
}


void create_observer(TaskBuffer buffer, Worker worker, Observer *observer)
{
    *observer = (Observer) malloc(sizeof(struct __Observer));

    (*observer)->observed_buffer = buffer;
    (*observer)->worker = worker;

    pthread_mutex_init(&(*observer)->end_search_lock, NULL);
}


void start_search(Observer observer)
{
    pthread_create(
        &observer->observer_thread_id,
        NULL,
        __observer_thread_code_wrapper,
        observer);
}


void end_search(Observer observer)
{
    pthread_mutex_lock(&(observer->end_search_lock));
        pthread_cancel(observer->observer_thread_id);
    pthread_mutex_unlock(&(observer->end_search_lock));
}


void delete_observer(Observer observer)
{
    pthread_mutex_destroy(&(observer->end_search_lock));
    free(observer);
}
