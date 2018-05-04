#ifndef ILOCOHANDLER_H
#define ILOCOHANDLER_H


#include <QThread>
#include <QSemaphore>
#include "locomotive.h"
#include <QList>

class ILocoHandler : public QThread {

protected:

    static bool isFree;
     static bool sens;
    QList<int> criticalSectionPoints = {4, 6, 5, 34, 33, 28};
    QList<int> criticalAig= {3,20};
    int startCS = 6;
    int endCS = 33;
     static QSemaphore* mutmut;
     static QSemaphore* busypath;

public:
    Locomotive* locomotive /*= new Locomotive()*/ ;


    ILocoHandler(){
        locomotive = new Locomotive();
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
            this->locomotive->inverserSens();
            this->locomotive->afficherMessage(QString("SENS INVERSED"));

            sens = !(sens);
        }
        this->locomotive->afficherMessage(QString("SENS INVERSED ? "));

    }
};
#endif // ILOCOHANDLER_H
