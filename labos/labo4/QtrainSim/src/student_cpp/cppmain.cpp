#include "ctrain_handler.h"
#include "locomotive.h"
#include "locohandler.h"

#include <iostream>
#include <QList>

//Creation d'une locomotive

LocoHandler locoH;
LocoHandler locoH2;


//Arret d'urgence
void emergency_stop()
{
    locoH.locomotive.arreter();
    afficher_message("\nSTOP!");
}




//Fonction principale
int cmain()
{
    afficher_message("Hit play to start the simulation...");

    //Choix de la maquette
    selection_maquette(MAQUETTE_A);

    //Initialisation d'un parcours
    QList<int> parcours;
    parcours << 16 << 15 << 14 << 7 << 6 << 5 << 34 << 33 << 32 << 25 << 24;


    //Initialisation des aiguillages
    diriger_aiguillage(8,  DEVIE,       0);
    diriger_aiguillage(2,  DEVIE,       0);
    diriger_aiguillage(20, DEVIE,       0);
    diriger_aiguillage(14, DEVIE,       0);
    diriger_aiguillage(11, TOUT_DROIT,  0);
    diriger_aiguillage(17, TOUT_DROIT,  0);
    diriger_aiguillage(23, TOUT_DROIT,  0);
    diriger_aiguillage(24, TOUT_DROIT,  0);
    diriger_aiguillage(6, TOUT_DROIT,  0);



    //Initialisation de la locomotive
    locoH.locomotive.fixerNumero(1);
    std::cout << locoH.locomotive.numero() << " COUCOU" << std::endl;
    locoH.locomotive.fixerVitesse(12);
    locoH.locomotive.fixerPosition(16,23);
    locoH.locomotive.allumerPhares();
    locoH.locomotive.setParcours(parcours);

    locoH2.locomotive.fixerNumero(2);
    locoH2.locomotive.fixerVitesse(13);
    //locomotive2.fixerPosition(35, 36); <-- BUG
    locoH2.locomotive.fixerPosition(9, 35);
    locoH2.locomotive.setParcours(parcours);
    locoH2.locomotive.allumerPhares();

    //locomotive.start();
    /*
    locomotive.demarrer();
    locomotive.afficherMessage("Ready!"); */
/*
    locomotive2.fixerNumero(2);
    locomotive2.fixerVitesse(13);
    //locomotive2.fixerPosition(35, 36); <-- BUG
    locomotive2.fixerPosition(9, 35);
    locomotive2.setParcours(parcours);
    locomotive2.allumerPhares();
    LocoHandler loco2(&locomotive2);

    //loco2.start();
*/
    locoH.start();
    locoH2.start();

    //locomotive2.start();


 /*   //Initialisation de la locomotive
    locomotive2.fixerNumero(2);
    locomotive2.fixerVitesse(12);
    locomotive2.fixerPosition(35, 36);
    locomotive2.allumerPhares();
    locomotive2.demarrer();
    locomotive2.afficherMessage("Ready!"); */


    //

    //Attente du passage sur les contacts
    /*for(int i = 0; i < 2; ++i){
        locomotive.parcourir(parcours);
        locomotive2.parcourir(parcours);
    }*/
    //locomotive.inverserSens();
    //locomotive2.inverserSens();
    //locomotive.parcourirInverse(parcours);
    //locomotive2.parcourirInverse(parcours);
    //Arreter la locomotive
    //locomotive.arreter();
    //locomotive2.arreter();
    locoH.locomotive.afficherMessage("Yeah, piece of cake!");

    //Fin de la simulation
    mettre_maquette_hors_service();

    //Exemple de commande
    afficher_message("Enter a command in the input field at the top of the window.");
    QString commande = getCommand();
    afficher_message(qPrintable(QString("Your command is: ") + commande));

    return EXIT_SUCCESS;
}


/*
//Fonction principale
int cmain()
{
    afficher_message("Hit play to start the simulation...");

    //Choix de la maquette
    selection_maquette(MAQUETTE_B);

    //Initialisation d'un parcours
    QList<int> parcours;
    parcours << 24 << 21 << 16 << 15 << 10 << 11 << 6 << 5;

    //Initialisation des aiguillages
    diriger_aiguillage(16, TOUT_DROIT,  0);
    diriger_aiguillage(15, DEVIE,       0);
    diriger_aiguillage(12, DEVIE,       0);
    diriger_aiguillage(11, DEVIE,       0);
    diriger_aiguillage(9,  TOUT_DROIT,  0);
    diriger_aiguillage(5,  TOUT_DROIT,  0);
    diriger_aiguillage(8,  DEVIE,       0);
    diriger_aiguillage(7,  TOUT_DROIT,  0);
    diriger_aiguillage(4,  TOUT_DROIT,  0);
    diriger_aiguillage(3,  TOUT_DROIT,  0);

    //Initialisation de la locomotive
    locomotive.fixerNumero(1);
    locomotive.fixerVitesse(12);
    locomotive.fixerPosition(24, 5);
    locomotive.allumerPhares();
    locomotive.demarrer();
    locomotive.afficherMessage("Ready!");

    //Attente du passage sur les contacts
    for (int i = 0; i < parcours.size(); i++) {
        attendre_contact(parcours.at(i));
        afficher_message(qPrintable(QString("The engine no. %1 has reached contact no. %2.")
                                    .arg(locomotive.numero()).arg(parcours.at(i))));
        locomotive.afficherMessage(QString("I've reached contact no. %1.").arg(parcours.at(i)));
    }

    //Arreter la locomotive
    locomotive.arreter();
    locomotive.afficherMessage("Yeah, piece of cake!");

    //Fin de la simulation
    mettre_maquette_hors_service();

    //Exemple de commande
    afficher_message("Enter a command in the input field at the top of the window.");
    QString commande = getCommand();
    afficher_message(qPrintable(QString("Your command is: ") + commande));

    return EXIT_SUCCESS;
}
*/
