#include "threadpool.h"
#include <QThread>


ThreadPool::ThreadPool(int maxThreadCount) : nbFreeThreads(maxThreadCount),
    maxThreadCount(maxThreadCount){
    dispoWorkers = new TPWorker[maxThreadCount];
}

void ThreadPool::start(Runnable *runnable){

}
