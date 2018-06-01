#include <QThread>
#include "response.h"
#include "abstractbuffer.h"
#include <QDebug>

class requestWorker : public QThread
{
private:
    Request r;
    AbstractBuffer<Response> *buff;

public:
    requestWorker(Request r, AbstractBuffer<Response> *buff) : r(r), buff(buff) {
        qDebug() << "Created requestWorker";

    }

protected:
    void run();

};
