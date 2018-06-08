#ifndef TPWORKER_H
#define TPWORKER_H
#include <QThread>

#include <QMutex>
#include <QWaitCondition>
#include "bufferimpl.h"
#include "requestworker.h"

class TPWorker : public QThread
{
private:
    QWaitCondition cond;
    QMutex mutex;

    bool hasWork;
    requestWorker* runnable;
    bufferImpl<TPWorker*>* idleThreads;
public:

    TPWorker();
    TPWorker( bufferImpl<TPWorker*>* idleThreads );
    bool isWorking();
    void setRunnable(Runnable* runnable);
    void run();
    void stop();
};

#endif // TPWORKER_H
