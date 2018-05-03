#include "locohandler2.h"
#include "ctrain_handler.h"
#include "locomotive.h"
#include <QThread>
#include <QSemaphore>

void LocoHandler2::setAiguillage(int numAig){
    if(isFree){
        mutmut->acquire();
        if(sens){
            // comment savoir quel aiguillage donner? dépend de la loco
        }else{

        }
        mutmut->release();
    }
}

void LocoHandler2::criticalSection(){
    busypath->acquire();
    // il faut ensuite parcourir le tronçon
    // puis release
}

void LocoHandler2::run(){
    this->locomotive->demarrer();

    for(int i = 0; i < this->locomotive->parcours().size(); ++i){
        attendre_contact(this->locomotive->parcours().at(i));
        this->locomotive->afficherMessage(QString("I've reached contact no. %1.").arg(this->locomotive->parcours().at(i)));
        if(sens && i == this->locomotive->startCS()){
            if(isFree){
                isFree = false;
                criticalSection();
                isFree = true;
            }else{
                // s'arrête ou prend le parcours d'urgence
                // modifie le i
            }
        }
        if(!sens && i == this->locomotive->endCS()){
            if(isFree){
                isFree = false;
                criticalSection();
                isFree = true;
            }else{
                //s'arrête ou prend le parcours d'urgence
                // modifie le i
            }
        }
    }
}

void LocoHandler2::emergencyPath(){
    for(int i = 0; i < this->locomotive->parcoursUrgence().size(); ++i){
        if(i == this->locomotive->parcoursUrgence().size()-1){
            // faire ce qu'il faut niveau aiguillage
        }
        attendre_contact(this->locomotive->parcoursUrgence().at(i));
        this->locomotive->afficherMessage(QString("I've reached contact no. %1.").arg(this->locomotive->parcours().at(i)));
    }
}
