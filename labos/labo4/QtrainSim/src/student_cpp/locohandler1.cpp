#include "locohandler1.h"
#include "ctrain_handler.h"
#include "locomotive.h"
#include <QThread>
#include <QSemaphore>
#include <iostream>

void LocoHandler1::setAiguillage(int numAig, int direction){
    // Prise du sémaphore pour sécuriser l'aiguillage
    mutmut->acquire();
    // Direction de l'aiguillage
    diriger_aiguillage(numAig, direction, 0);
    // Relâchement du sémaphore
    mutmut->release();
}

void LocoHandler1::criticalSectionStart(){
    // Prise du sémaphore pour protéger la section critique
    busypath->acquire();
    // Indication que la section critique est occupée
    isFree = false;
    // Direction des aiguillages pour entrer en section critique
    setAiguillage(evitmentAig.at(0), DEVIE);
    setAiguillage(criticalAig.at(0), TOUT_DROIT);
}

void LocoHandler1::criticalSectionEnd(){
    // Direction de l'aiguillage pour sortir de la section critique
    setAiguillage(criticalAig.at(1), TOUT_DROIT);
    // Attente du dernier point de contrôle
    attendre_contact(checkPoints.last());
    // Indication que la section critique est libre
    isFree = true;
    // Relâchement du sémaphore
    busypath->release();
}

void LocoHandler1::evitmentSectionStart(){
    // Direction de l'aguillage pour entrer dans la voie d'évitement
    setAiguillage(evitmentAig.at(0), TOUT_DROIT);
    // Passage du parcours principal au parcours d'évitement
    this->locomotive->switchParcours();
}
void LocoHandler1::evitmentSectionEnd(){
    // Direction de l'aiguillage pour sortir de la voie d'évitement
    setAiguillage(evitmentAig.at(1), TOUT_DROIT);
    // Passage du parcours d'évitement au parcours principal
    this->locomotive->switchParcours();

}

void LocoHandler1::changeSens(bool newSens) {
    ILocoHandler::changeSens(newSens);
    // Inversion de toutes les listes
    std::reverse(checkPoints.begin(), checkPoints.end());
    std::reverse(evCheckPoints.begin(), evCheckPoints.end());
    std::reverse(evitmentAig.begin(), evitmentAig   .end());

}

void LocoHandler1::run(){
    this->locomotive->demarrer();
    // Pour
    int tmp;
while(true){
    // Deux tours dans chaque sens
    for(int j =0;j <2;j++){
    for(int i = 0; i < this->locomotive->parcours().size(); ++i){
        attendre_contact(this->locomotive->parcours().at(i));
        this->locomotive->afficherMessage(QString("I've reached contact no. %1.").arg(this->locomotive->parcours().at(i)));
        // Si la locomotive arrive en entrée de section critique
        if(this->locomotive->parcours().at(i) == CS_ENTRY) {
            // Si la voie est libre ou que sa priorité l'accepte
            if(isFree && (locoPriority == locomotive->numero() || locoPriority == 0) ){
                // Entrée en section critique
                criticalSectionStart();
            }else{ // Si la voie n'est pas libre ou que la locomotive n'a pas la priorité adaptée
                // Entrée en voie d'évitement
                evitmentSectionStart();
                this->locomotive->afficherMessage(QString("size. %1.").arg(this->locomotive->parcours().size() ));
                // Sauvegarde du point de passage actuel de la locomotive
                tmp = i;
                i = -1; // Parce qu'on fait i++ à la fin de l'itération

            }
            // Si la locomotive arrive en sortie de section critique
        }else if(locomotive->parcours().at(i) == CS_EXIT){
            // Sortie de la section critique
            criticalSectionEnd();
            // Parce qu'on appelle attendre_contact dans la fonction précédente
            i += 2;
            // Si la locomotive arrive en sortie de voie d'évitement
        }else if(locomotive->parcours().at(i) == ES_EXIT){
            // Sortie de la voie d'évitement
            evitmentSectionEnd();
            this->locomotive->afficherMessage(QString("End of evitment"));
            // Retour au premier point après section critique
            i = tmp + 4;
        }
    }
    }

    changeSens(!sens);
}
}

