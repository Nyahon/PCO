#ifndef ILOCOHANDLER_H
#define ILOCOHANDLER_H

#include <QThread>
#include <QSemaphore>
#include "locomotive.h"
#include <QList>

class ILocoHandler : public QThread {

private:

    bool isFree;
    bool sens = true;
    QList<int> criticalSectionPoints {4, 6, 5, 34, 33, 28};
    QList<int> criticalAig {3,20};
    int startCS = 6;
    int endCS = 33;
    QSemaphore* mutmut;
    QSemaphore* busypath;

public:
    Locomotive* locomotive;

    virtual void setAiguillage(bool isFree, int sens, int numAig ) = 0;
    virtual void criticalSection( bool isFree  ) = 0;
    virtual void run() = 0;
    void changeSens(bool newSens) {
        if(sens != newSens){
            std::reverse(criticalSectionPoints.begin(), criticalSectionPoints.end());
            sens = !sens;
        }
    }
};
#endif // ILOCOHANDLER_H
