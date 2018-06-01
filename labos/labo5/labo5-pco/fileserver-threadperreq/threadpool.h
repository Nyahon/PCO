#ifndef THREADPOOL_H
#define THREADPOOL_H

#include "runnable.h"


class ThreadPool
{
public:
    ThreadPool(int maxThreadCount);
    void start(Runnable* runnable);
};

#endif // THREADPOOL_H
