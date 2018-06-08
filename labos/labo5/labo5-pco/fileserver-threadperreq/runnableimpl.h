#ifndef RUNNABLEIMPL
#define RUNNABLEIMPL

#include "runnable.h"
#include <QThread>
#include <QString>
#include "request.h"
#include "response.h"

class RunnableImpl : public Runnable, QThread {
public:
    RunnableImpl(requestWorker* worker) : worker(worker){}
    void run(){
      //  worker->start();
    }
private:
    requestWorker* worker;
};

#endif // RUNNABLEIMPL

