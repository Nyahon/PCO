#ifndef THREADPOOL_H
#define THREADPOOL_H

#include "runnable.h"
#include "tpworker.h"


class ThreadPool
{
public:
    ThreadPool(int maxThreadCount);
    void start(Runnable* runnable);
private:
    int maxThreadCount, nbFreeThreads;
    //list of disponible workers
    TPWorker* dispoWorkers;
};


#endif // THREADPOOL_H
