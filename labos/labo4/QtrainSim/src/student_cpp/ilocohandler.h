#ifndef ILOCOHANDLER_H
#define ILOCOHANDLER_H


#include <QThread>
#include <QSemaphore>
#include "locomotive.h"
#include <QList>

class ILocoHandler : public QThread {

protected:

    bool isFree;
    bool sens = true;
    QList<int> criticalSectionPoints {4, 6, 5, 34, 33, 28};
    QList<int> criticalAig {3,20};
    int startCS = 6;
    int endCS = 33;
    QSemaphore* mutmut;
    QSemaphore* busypath;

public:
    Locomotive* locomotive /*= new Locomotive()*/ ;


    ILocoHandler() {
        mutmut = new QSemaphore(1);
        busypath = new QSemaphore(1);
        locomotive = new Locomotive();
        isFree = true;
    }
    virtual void setAiguillage(int numAig, int direction) = 0;
    virtual void criticalSectionStart() = 0;
    virtual void criticalSectionEnd() = 0;
    virtual void run() = 0;
    void changeSens(bool newSens) {
        if(sens != newSens){
            std::reverse(criticalSectionPoints.begin(), criticalSectionPoints.end());
            std::reverse(criticalAig.begin(), criticalAig.end());
            this->locomotive->inverserSensParcours();
            sens = !sens;
        }
    }
};
#endif // ILOCOHANDLER_H
