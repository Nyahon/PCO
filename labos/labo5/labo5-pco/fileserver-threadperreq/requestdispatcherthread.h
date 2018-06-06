#ifndef REQUESTDISPATCHERTHREAD_H
#define REQUESTDISPATCHERTHREAD_H
#include <QObject>
#include <QThread>
#include <QDebug>
#include "abstractbuffer.h"
#include "request.h"
#include "requestworker.h"
#include "runnableimpl.h"
#include <QList>

class requestDispatcherThread : public QThread
{
    Q_OBJECT

public:
    requestDispatcherThread(AbstractBuffer<Request>* requests, AbstractBuffer<Response>* responses,  bool hasDebugLog):
        requests(requests),
        responses(responses),
        hasDebugLog(hasDebugLog) {
        if (hasDebugLog)
            qDebug() << "Created request dispatcher thread";
        qRegisterMetaType<Request>("Request");
    }

protected:
    void run();

private:
    AbstractBuffer<Request>* requests;
    AbstractBuffer<Response>* responses;

    bool hasDebugLog;
    QList<requestWorker*> procList;

};

#endif // REQUESTDISPATCHERTHREAD_H
