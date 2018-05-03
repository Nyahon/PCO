#ifndef LOCOHANDLER2_H
#define LOCOHANDLER2_H
#include "ctrain_handler.h"
#include "locomotive.h"
#include <QThread>
#include <QSemaphore>
class LocoHandler2 : public QThread {

private:

    bool isFree;
    bool sens;
    QSemaphore* mutmut;
    QSemaphore* busypath;
    Locomotive* locomotive;

public:
    void setAiguillage(int numAig);
    void criticalSection();
    void run();
    void emergencyPath();

};
#endif // LOCOHANDLER2_H
