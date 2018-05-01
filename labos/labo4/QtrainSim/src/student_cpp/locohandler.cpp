#include "locohandler.h"
#include "ctrain_handler.h"
#include "locomotive.h"

LocoHandler::LocoHandler(){

}

void LocoHandler::run(){



    this->locomotive.start();

    for(int j = 0; j < 2; ++j){
        for (int i = 0; i < this->locomotive.parcours().size(); i++) {

           attendre_contact(this->locomotive.parcours().at(i));
           afficher_message(qPrintable(QString("The engine no. %1 has reached contact no. %2.")
                                       .arg(this->locomotive.numero()).arg(this->locomotive.parcours().at(i))));
           this->locomotive.afficherMessage(QString("I've reached contact no. %1.").arg(this->locomotive.parcours().at(i)));

        }
    }

    this->locomotive.inverserSens();

    for (int i = this->locomotive.parcours().size()-1; i >= 0 ; i--) {

       attendre_contact(this->locomotive.parcours().at(i));
       afficher_message(qPrintable(QString("The engine no. %1 has reached contact no. %2.")
                                   .arg(this->locomotive.numero()).arg(this->locomotive.parcours().at(i))));
       this->locomotive.afficherMessage(QString("I've reached contact no. %1.").arg(this->locomotive.parcours().at(i)));

    }

    this->locomotive.arreter();
}
