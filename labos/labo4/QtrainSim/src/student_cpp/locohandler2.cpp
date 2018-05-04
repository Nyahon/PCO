#include "locohandler2.h"
#include "ctrain_handler.h"
#include "locomotive.h"
#include <QThread>
#include <QSemaphore>



void LocoHandler2::setAiguillage(int numAig, int direction){
    // Sécurisation de l'aiguillage avec un sémaphore
    mutmut->acquire();
    // Direction de l'aiguillage
    diriger_aiguillage(numAig, direction, 0);
    // Relâchement du sémaphore
    mutmut->release();
}

void LocoHandler2::criticalSectionStart(){

    this->locomotive->afficherMessage(QString("I've reached critical section."));
    // Prend le sémaphore de la section critique
    busypath->acquire();
    this->locomotive->afficherMessage(QString("I got the mutex."));
    // Indique que la section critique est occupée
    isFree = false;
    // Dirige l'aiguillage d'entrée de la section critique
    setAiguillage(criticalAig.at(0), DEVIE);

}

void LocoHandler2::criticalSectionEnd(){
    // Dirige l'aiguillage de sortie de la section critique
    setAiguillage(criticalAig.at(1), DEVIE);
    // Indique que la voie est libre
    isFree = true;
    // Relâche le sémaphore
    busypath->release();
}

void LocoHandler2::run(){
    // Lancement de la locomotive
    this->locomotive->demarrer();
    //Boucle infinie pour le parcours de la locomotive
while(true) {
    // Doit faire deux tour dans chaque sens
    for(int j =0;j <2;j++){
        // Itération sur le parcours de la locomotive
    for(int i = 0; i < this->locomotive->parcours().size(); ++i){
        // Attente du passage de la locomotive sur le point de passage de son parcours
        attendre_contact(this->locomotive->parcours().at(i));
        this->locomotive->afficherMessage(QString("I've reached contact no. %1.").arg(this->locomotive->parcours().at(i)));
        // Si la locomotive arrive devant la section critique
        if(this->locomotive->parcours().at(i) == CS_ENTRY){
            // Dans le cas où la la section est libre
            if(isFree && (locoPriority == locomotive->numero() || locoPriority == 0) ){
                this->locomotive->afficherMessage(QString("It's free!"));
                // Entrée en section critique
                criticalSectionStart();
          }else{ // Si la section n'est pas libre
                // La locomotive s'arrête
               this->locomotive->arreter();
                // Blocage tant que la section critique est occupée, prise du sémaphore
                busypath->acquire();
                // Direction de l'aiguillage pour l'entrée en section critique
                setAiguillage(criticalAig.at(0), DEVIE);
                // Redémarrage de la locomotive
                this->locomotive->demarrer();
            }
            // Si la locomotive arrive devant la sortie de la section critique
        }else if(this->locomotive->parcours().at(i) == CS_EXIT){
            // Sortie de la section critique
            criticalSectionEnd();
        }
    }
    }
    // Changement de sens de la locomotive
    changeSens(!sens);


}

}

//! Redéfinition de changeSens
void LocoHandler2::changeSens(bool newSens) {
    ILocoHandler::changeSens(newSens);
    // La liste des checkPoints est inversée
    std::reverse(checkPoints.begin(), checkPoints.end());
}

