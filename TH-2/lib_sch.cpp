#include "lib_sch.h"
#include <iostream>

parallel_scheduler::parallel_scheduler(int count)
{
    thread_count = count;
    stop_flag = 0;

    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&wake, NULL);

    pool = new pthread_t[thread_count];

    for (int i = 0; i < thread_count; i++) {
        pthread_create(&pool[i], NULL, thread_loop, this);
    }
}

parallel_scheduler::~parallel_scheduler()
{
    pthread_mutex_lock(&lock);
    stop_flag = 1;
    pthread_mutex_unlock(&lock);

    pthread_cond_broadcast(&wake);

    for (int i = 0; i < thread_count; i++) {
        pthread_join(pool[i], NULL);
    }

    delete[] pool;

    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&wake);
}

void* parallel_scheduler::thread_loop(void* arg)
{
    parallel_scheduler* self = (parallel_scheduler*)arg;

    while (true) {
        pthread_mutex_lock(&self->lock);

        while (self->jobs.empty() && self->stop_flag == 0) {
            pthread_cond_wait(&self->wake, &self->lock);
        }

        if (self->stop_flag == 1 && self->jobs.empty()) {
            pthread_mutex_unlock(&self->lock);
            return NULL;
        }

        job* j = self->jobs.front();
        self->jobs.pop();

        pthread_mutex_unlock(&self->lock);

        j->action();
        delete j;
    }
}

void parallel_scheduler::run(void (*func)(int), int value)
{
    job* j = new job;
    j->action = [func, value]() { func(value); };

    pthread_mutex_lock(&lock);
    jobs.push(j);
    pthread_cond_signal(&wake);
    pthread_mutex_unlock(&lock);
}

