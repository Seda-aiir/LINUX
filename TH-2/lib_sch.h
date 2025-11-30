#ifndef MY_PAR_SCHEDULER_H
#define MY_PAR_SCHEDULER_H

#include <pthread.h>
#include <queue>
#include <functional>

struct job {
    std::function<void()> action;
};

class parallel_scheduler {
public:
    parallel_scheduler(int count);
    ~parallel_scheduler();

    void run(void (*func)(int), int value);

private:
    int thread_count;
    int stop_flag;

    std::queue<job*> jobs;
    pthread_t* pool;

    pthread_mutex_t lock;
    pthread_cond_t wake;

    static void* thread_loop(void* arg);
};

#endif

