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
    busypath->acquire();
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

