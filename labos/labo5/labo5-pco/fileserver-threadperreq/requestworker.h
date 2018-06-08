#pragma once

#pragma once

#include <QThread>
#include "response.h"
#include "abstractbuffer.h"
#include <QDebug>
#include "runnable.h"

class requestWorker : public Runnable {
private:
    Request r;
    AbstractBuffer<Response> *buff;
    bool done;
    QString workerId;

public:
    requestWorker(Request r, AbstractBuffer<Response> *buff) : r(r), buff(buff), done(false) {
        qDebug() << "Created requestWorker";

    }
    bool isFinished();

    QString id(){
        return workerId;
    }
    ~requestWorker();
public:
    void run();

};
