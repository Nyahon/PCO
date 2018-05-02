#include "locohandler.h"
#include "ctrain_handler.h"
#include "locomotive.h"
#include <iostream>
#include <vector>
//A METTRE DANS LE .h
const int BEF_CS = 28;
const int AFT_CS = 4;
const int IN_CS = 33;
const int OUT_CS = 6;
const std::vector<int> CS_SECTIONS {BEF_CS, AFT_CS, IN_CS, OUT_CS};
bool isFree;

LocoHandler::LocoHandler() :  sem( new QSemaphore(1)) , mutex( new QSemaphore(1) ) {
    this->locomotive = new Locomotive();
}

void LocoHandler::run(){
    bool sens = true;

    this->locomotive->demarrer();

    for(int j = 0; j < 2; ++j){

        for (int i = 0; i < this->locomotive->parcours().size(); i++) {

           //lockSeg(); //TODO
        //   sem->acquire();
            if(this->locomotive->numero() == 1)
                checkStateLoco1(sens, &i);
            if(this->locomotive->numero() == 2)
                checkStateLoco2(sens, &i );

/*
            if(i == BEF_CS || i == AFT_CS ){
                setAiguillage(this->locomotive->numero(), this->locomotive->parcours().at(i), this->locomotive->parcours().at(i+1));
            } */
           attendre_contact(this->locomotive->parcours().at(i));

        //   afficher_message(qPrintable(QString("The engine no. %1 has reached contact no. %2.")
         //                              .arg(this->locomotive->numero()).arg(this->locomotive->parcours().at(i))));
       /*    sem->acquire();
           locomotive->afficherMessage(QString("I've reached contact no. %1. I'm %2").arg(this->locomotive->parcours().at(i)).arg(this->locomotive->numero()));
            sem->release();*/
        }
    }

    this->locomotive->inverserSens();
    sens = false;
  //  std::reverse(locomotive->parcours().begin(), locomotive->parcours().end());

    for (int i = this->locomotive->parcours().size()-1; i >= 0 ; i--) {

       attendre_contact(this->locomotive->parcours().at(i));
       afficher_message(qPrintable(QString("The engine no. %1 has reached contact no. %2.")
                                   .arg(this->locomotive->numero()).arg(this->locomotive->parcours().at(i))));
       this->locomotive->afficherMessage(QString("I've reached contact no. %1.").arg(this->locomotive->parcours().at(i)));

    }

    this->locomotive->arreter();
}

void LocoHandler::checkStateLoco1(bool sens, int* x){
    int i = *x;
    int loc = locomotive->parcours().at(i);

    mutex->acquire();
    locomotive->afficherMessage(QString("GOT MUTEX"));
    if(sens && loc == 4){
        locomotive->afficherMessage(QString("NUMERO 4"));

        diriger_aiguillage(3, TOUT_DROIT,  0);

        //entry
        if(isFree){
            diriger_aiguillage(4, DEVIE, 0);

            diriger_aiguillage(2, DEVIE, 0);
            isFree = false;

            //attendre_contact( 33 );
            locomotive->afficherMessage(QString("CC C LIBR"));

            locomotive->afficherMessage(QString("I've reached contact no. %1. I'm %2").arg(this->locomotive->parcours().at(i)).arg(this->locomotive->numero()));

            diriger_aiguillage(20, TOUT_DROIT, 0 );
            isFree = true;



        }else{
            locomotive->afficherMessage(QString("YO C MOR"));
            QList<int> parcoursUrgence;
            parcoursUrgence << 3 << 2 << 1 << 31 << 30;
            *x = 0;

            locomotive->setParcours(parcoursUrgence);

            diriger_aiguillage(2, TOUT_DROIT, 0);
            locomotive->afficherMessage(QString("I've reached contact no. %1. I'm %2").arg(this->locomotive->parcours().at(i)).arg(this->locomotive->numero()));
            diriger_aiguillage(22, TOUT_DROIT, 0);
            diriger_aiguillage(19, TOUT_DROIT, 0);


        }
        diriger_aiguillage(2, DEVIE, 0);

        //during



    }

    locomotive->afficherMessage(QString("RELEASE MUTEX"));

    mutex->release();
}




void LocoHandler::checkStateLoco2(bool sens, int* x){
    int i = *x;
    int loc = locomotive->parcours().at(i);

    mutex->acquire();
    locomotive->afficherMessage(QString("GOT MUTEX"));

    if(sens && loc == 8){
        locomotive->afficherMessage(QString("ON EST AU 8"));

        diriger_aiguillage(3, DEVIE,  0);

        //entry
        if(isFree){
            if(locomotive->vitesse() == 0){
                locomotive->demarrer();
            }

            diriger_aiguillage(2, DEVIE, 0);
            isFree = false;

            attendre_contact( 33 );
            locomotive->afficherMessage(QString("I've reached contact no. %1. I'm %2").arg(this->locomotive->parcours().at(i)).arg(this->locomotive->numero()));

            diriger_aiguillage(20, DEVIE, 0 );
            isFree = true;



        }else{
            locomotive->arreter();
            diriger_aiguillage(2, TOUT_DROIT, 0);

        }
    }
    locomotive->afficherMessage(QString("RELEASE MUTEX"));
    mutex->release();
}
void LocoHandler::setAiguillage(int no, int frontpoint, int sens){

}
void LocoHandler::lockSeg(int no, int backpoint, int frontpoint){

    //mmh,possible problem with too long time to acquire ?
    mutex->acquire();


}
