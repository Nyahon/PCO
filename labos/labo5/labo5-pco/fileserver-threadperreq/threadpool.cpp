#include "threadpool.h"
#include <QThread>


ThreadPool::ThreadPool(int maxThreadCount) : nbFreeThreads(maxThreadCount),
    maxThreadCount(maxThreadCount), idleThreads(maxThreadCount){


  //  dispoWorkers = new TPWorker[maxThreadCount];
    // idleThreads = new QList<TPWorker>(maxThreadCount);
}

void ThreadPool::start(Runnable *runnable){

    mutex.lock();

    //We do the following if else in that order to prevent
    // the creation of a new thread if the pool contains one
    // or more idle thread(s).

    //check if we have an idle thread
    if(idleThreads.getSize() !=0){
        TPWorker* tpW = idleThreads.get();
        tpW->setRunnable(runnable);

    }
    //else check if we can create one more thread
    else if(threadPool.size() < maxThreadCount){
        TPWorker* tpW = new TPWorker();
        threadPool.push_back( tpW );

        tpW->start();
        tpW->setRunnable(runnable);
     //else wait for a thread to become idle
    }else{
        while(idleThreads.getSize() == 0){
            cond.wait(&mutex);
        }
        TPWorker* tpW = idleThreads.get();
        tpW->setRunnable(runnable);

    }
    mutex.unlock();
}



void ThreadPool::pushIdleThread(TPWorker* tpW){
    idleThreads.put( tpW );
}

TPWorker* ThreadPool::removeIdleThread(){
    /*
     int id;
    if( (id = idleThreads.indexOf( tpW ) ) != 0){
        idleThreads.removeAt(id);
    } */
    return idleThreads.get();
    //TODO exception handling
}

