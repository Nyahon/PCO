#include "locohandler2.h"
#include "ctrain_handler.h"
#include "locomotive.h"
#include <QThread>
#include <QSemaphore>

void LocoHandler2::setAiguillage(int numAig, int direction){
    mutmut->acquire();
    diriger_aiguillage(numAig, direction, 0);
    mutmut->release();
}

void LocoHandler2::criticalSectionStart(){

    this->locomotive->afficherMessage(QString("I've reached critical section."));
    busypath->acquire();
    this->locomotive->afficherMessage(QString("I got the mutex."));
    isFree = false;
    setAiguillage(criticalAig.at(0), DEVIE);

}

void LocoHandler2::criticalSectionEnd(){
    setAiguillage(criticalAig.at(4), DEVIE);
    isFree = true;
    busypath->release();
}

void LocoHandler2::run(){
    this->locomotive->demarrer();

    for(int i = 0; i < this->locomotive->parcours().size(); ++i){
        attendre_contact(this->locomotive->parcours().at(i));
        this->locomotive->afficherMessage(QString("I've reached contact no. %1.").arg(this->locomotive->parcours().at(i)));
        if(this->locomotive->parcours().at(i) == CS_ENTRY){
           if(isFree){
                this->locomotive->afficherMessage(QString("It's free!"));
                criticalSectionStart();
          }else{
                arreter_loco(this->locomotive->numero());
                busypath->acquire();
                this->locomotive->demarrer();
                setAiguillage(criticalAig.at(0), DEVIE);
            }
        }else if(i == CS_EXIT){
            criticalSectionEnd();
        }
    }

}


void LocoHandler2::changeSens(bool newSens) {
    ILocoHandler::changeSens(newSens);
    std::reverse(checkPoints.begin(), checkPoints.end());
}

