#ifndef ILOCOHANDLER_H
#define ILOCOHANDLER_H

#include <QThread>
#include <QSemaphore>
#include "locomotive.h"

class ILocoHandler : public QThread {

private:

    bool isFree;
    bool sens = true;
    Qlist<int> criticalSection {4, 6, 5, 34, 33, 28};
    Qlist<int> criticalAig {3,20};
    int startCS = 6;
    int endCS = 33;
    QSemaphore* mutmut;
    QSemaphore* busypath;

public:
    Locomotive* loco;

    virtual void setAiguillage(bool isFree, int sens, int numAig );
    virtual void criticalSection( bool isFree  );
    virtual void run();
    void changeSens(bool newSens) {
        if(sens != newSens){
            std::reverse(criticalSection.begin(), criticalSection.end());
            sens = !sens;
        }
    }
}
#endif // ILOCOHANDLER_H
