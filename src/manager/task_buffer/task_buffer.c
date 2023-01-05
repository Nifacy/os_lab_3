#include "task_buffer.h"
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>


struct __TaskBuffer
{
    int free_cell_index;
    Task *buffer;
    
    pthread_mutex_t edit_buffer_mutex;
    sem_t free_cells;
    sem_t untaken_tasks;
};


void create_task_buffer(int buffer_size, TaskBuffer *buffer)
{
    *buffer = (TaskBuffer) malloc(sizeof(struct __TaskBuffer));
    (*buffer)->free_cell_index = 0;
    (*buffer)->buffer = (Task *) calloc(buffer_size, sizeof(Task));
    
    pthread_mutex_init(&(*buffer)->edit_buffer_mutex, NULL);
    sem_init(&(*buffer)->free_cells, 0, buffer_size);
    sem_init(&(*buffer)->untaken_tasks, 0, 0);
}


void add_task(Task task, TaskBuffer buffer)
{
    sem_wait(&(buffer->free_cells));
        pthread_mutex_lock(&(buffer->edit_buffer_mutex));
            buffer->buffer[buffer->free_cell_index] = task;
            buffer->free_cell_index++;
        pthread_mutex_unlock(&(buffer->edit_buffer_mutex));
    sem_post(&(buffer->untaken_tasks));
}


Task get_task(TaskBuffer buffer)
{
    sem_wait(&(buffer->untaken_tasks));
        pthread_mutex_lock(&(buffer->edit_buffer_mutex));
            Task task = buffer->buffer[buffer->free_cell_index - 1];
            buffer->free_cell_index--;
        pthread_mutex_unlock(&(buffer->edit_buffer_mutex));
    sem_post(&(buffer->free_cells));
    
    return task;
}


bool is_empty(TaskBuffer buffer)
{
    pthread_mutex_lock(&(buffer->edit_buffer_mutex));
        bool result = buffer->free_cell_index == 0;
    pthread_mutex_unlock(&(buffer->edit_buffer_mutex));
    
    return result;
}


void delete_task_buffer(TaskBuffer buffer)
{
    pthread_mutex_destroy(&(buffer->edit_buffer_mutex));
    free(buffer->buffer);
    free(buffer);
}
