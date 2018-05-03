#include "locohandler1.h"
#include "ctrain_handler.h"
#include "locomotive.h"
#include <QThread>
#include <QSemaphore>

//TEMP
#include <iostream>

void LocoHandler1::setAiguillage(int numAig, int direction){
    mutmut->acquire();
    diriger_aiguillage(numAig, direction, 0);
    mutmut->release();
}

void LocoHandler1::criticalSectionStart(){
    busypath->acquire();
    isFree = false;
    this->locomotive->afficherMessage(QString("UNFREE"));

    setAiguillage(criticalAig.at(0), DEVIE);

}

void LocoHandler1::criticalSectionEnd(){
    setAiguillage(criticalAig.at(1), TOUT_DROIT);
    isFree = true;
    busypath->release();
}

void LocoHandler1::run(){
    this->locomotive->demarrer();

    for(int i = 0; i < this->locomotive->parcours().size(); ++i){
        attendre_contact(this->locomotive->parcours().at(i));
        this->locomotive->afficherMessage(QString("I've reached contact no. %1.").arg(this->locomotive->parcours().at(i)));
        this->locomotive->afficherMessage(QString("isFree:  %1.").arg( isFree ));

        if(this->locomotive->parcours().at(i) == CS_ENTRY) {
            this->locomotive->afficherMessage(QString("LOLOLO"));

            if(isFree){
                criticalSectionStart();
            }else{
                arreter_loco(this->locomotive->numero());
                busypath->acquire();
                this->locomotive->demarrer();
                setAiguillage(criticalAig.at(0), DEVIE);
            }
        }else if(locomotive->parcours().at(i) == CS_EXIT){
            criticalSectionEnd();
        }
    }

}

