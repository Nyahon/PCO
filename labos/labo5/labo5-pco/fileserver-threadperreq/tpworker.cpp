#include "tpworker.h"
#include "threadpool.h"

TPWorker::TPWorker() : hasWork(false)
{

}

TPWorker::TPWorker(bufferImpl<TPWorker*>* idleThreads ) : hasWork(false), idleThreads(idleThreads)
{

}

void TPWorker::setRunnable(Runnable *runnable){
    mutex.lock();

    this->runnable = (requestWorker*) runnable;
    hasWork = true;

    //start working
    cond.wakeOne();

    mutex.unlock();
}

void TPWorker::run(){
    while(!QThread::currentThread()->isInterruptionRequested() ){

        mutex.lock();

        while(!hasWork){
            cond.wait(&mutex);
        }

        mutex.unlock();
        //do the work, work
        runnable->run();

        mutex.lock();

        hasWork = false;
        idleThreads->put(this);
        mutex.unlock();

    }
}

void TPWorker::stop(){
    mutex.lock();

    this->requestInterruption();
    cond.wakeOne();
    mutex.unlock();
}
