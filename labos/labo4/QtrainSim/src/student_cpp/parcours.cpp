#include "parcours.h"
Parcours::Parcours(QList<int> parcours){
    this->parcours = parcours;
}

void Parcours::run(){
    for (int i = 0; i < this->_parcours.size(); i++) {

       attendre_contact(this->_parcours.at(i));
       afficher_message(qPrintable(QString("The engine no. %1 has reached contact no. %2.")
                                   .arg(this->numero()).arg(this->parcours.at(i))));
       this->afficherMessage(QString("I've reached contact no. %1.").arg(this->parcours.at(i)));
   }
}
