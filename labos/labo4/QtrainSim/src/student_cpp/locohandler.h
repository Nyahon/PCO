#ifndef LOCOHANDLER
#define LOCOHANDLER
#include <QThread>
#include <QSemaphore>
#include "locomotive.h"



class LocoHandler : public QThread {
public:
    Locomotive* locomotive;

    LocoHandler();
    //! implementation QThread
    void run();
    void lockSeg(int no, int backpoint, int frontpoint);
    void checkStateLoco1(bool sens, int* loc);
    void checkStateLoco2(bool sens, int* loc);
    void setAiguillage(int no, int frontpoint, int sens);



private:
    int priorite;
    QSemaphore* sem;
    QSemaphore* mutex;

 };

#endif // LOCOHANDLER

