#ifndef THREADPOOL_H
#define THREADPOOL_H

#include "runnable.h"
#include "tpworker.h"
#include "bufferimpl.h"

class ThreadPool
{
public:
    ThreadPool(int maxThreadCount);
    void start(Runnable* runnable);
    void stop();

    void pushIdleThread(TPWorker* tpW);
    TPWorker* removeIdleThread();

    friend void TPWorker::run();
    friend void TPWorker::stop();

private:
    QWaitCondition cond;
    QMutex mutex;

    int maxThreadCount, nbFreeThreads;
    //list of disponible workers
   // TPWorker* dispoWorkers;
    bufferImpl<TPWorker*> idleThreads;
    QList<TPWorker*> threadPool;


};


#endif // THREADPOOL_H
