#include "worker.h"
#include "../matrix/matrix.h"
#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>


struct __Worker
{
    pthread_t id;
    Task task;
    bool is_busy;
};


void __worker_code(PMatrix a, PMatrix b, int i, int j, PMatrix c)
{
    MatrixElement result = 0;

    for (int p = 0; p < cols(a); p++) {
        MatrixElement a_element;
        MatrixElement b_element;

        get_cell(i, p, a, &a_element);
        get_cell(p, j, b, &b_element);

        result += a_element * b_element;
    }

    set_cell(i, j, result, c);
}


void *__worker_code_wrapper(void *data)
{
    Worker worker = (Worker) data;

    __worker_code(
        worker->task.a, worker->task.b,
        worker->task.i, worker->task.j,
        worker->task.out_matrix
    );

    worker->is_busy = false;
    pthread_exit(0);
}


void create_worker(Worker *worker)
{
    *worker = (Worker) malloc(sizeof(struct __Worker));
    (*worker)->is_busy = false;
}


void run_task(Task task, Worker worker)
{
    worker->task = task;
    worker->is_busy = true;
    pthread_create(&worker->id, NULL, __worker_code_wrapper, worker);
}


void wait_worker(Worker worker)
{
    pthread_join(worker->id, NULL);
}


void delete_worker(Worker worker)
{
    free(worker);
}


bool is_busy(Worker worker)
{
    return worker->is_busy;
}
