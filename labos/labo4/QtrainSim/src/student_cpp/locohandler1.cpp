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

    setAiguillage(evitmentAig.at(0), DEVIE);
    setAiguillage(criticalAig.at(0), TOUT_DROIT);


}

void LocoHandler1::criticalSectionEnd(){
    setAiguillage(criticalAig.at(1), TOUT_DROIT);
    attendre_contact(checkPoints.last());
    isFree = true;
    busypath->release();
}

void LocoHandler1::evitmentSectionStart(){
    setAiguillage(evitmentAig.at(0), TOUT_DROIT);
    this->locomotive->switchParcours();
}
void LocoHandler1::evitmentSectionEnd(){
    setAiguillage(evitmentAig.at(1), TOUT_DROIT);
    this->locomotive->switchParcours();

}

void LocoHandler1::changeSens(bool newSens) {
    //this->locomotive->afficherMessage(QString("HERE INVERSED"));
    ILocoHandler::changeSens(newSens);
    std::reverse(checkPoints.begin(), checkPoints.end());
    std::reverse(evCheckPoints.begin(), evCheckPoints.end());
    std::reverse(evitmentAig.begin(), evitmentAig   .end());

}

void LocoHandler1::run(){
    this->locomotive->demarrer();
    int tmp;
    QList<int> tmpP;
while(true){
    for(int j =0;j <2;j++){

    for(int i = 0; i < this->locomotive->parcours().size(); ++i){
        this->locomotive->afficherMessage(QString("WAITING contact no. %1.").arg(this->locomotive->parcours().at(i)));

        attendre_contact(this->locomotive->parcours().at(i));
        this->locomotive->afficherMessage(QString("I've reached contact no. %1.").arg(this->locomotive->parcours().at(i)));
        this->locomotive->afficherMessage(QString("isFree:  %1.").arg( isFree ));

        if(this->locomotive->parcours().at(i) == CS_ENTRY) {
            this->locomotive->afficherMessage(QString("LOLOLO"));

            if(isFree && (locoPriority == locomotive->numero() || locoPriority == 0) ){
                criticalSectionStart();

            }else{
                evitmentSectionStart();
                this->locomotive->afficherMessage(QString("size. %1.").arg(this->locomotive->parcours().size() ));

                tmp = i;
                i = -1; //cause we do i++ at end of iteration

            }
        }else if(locomotive->parcours().at(i) == CS_EXIT){
            criticalSectionEnd();
            i+=2;

        }else if(locomotive->parcours().at(i) == ES_EXIT){
            evitmentSectionEnd();
            this->locomotive->afficherMessage(QString("EV END"));

            i = tmp + 4; //TODO extract number of point IN critical section

        }
    }
    }

    changeSens(!sens);
}
}

