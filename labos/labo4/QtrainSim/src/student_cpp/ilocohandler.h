#ifndef ILOCOHANDLER_H
#define ILOCOHANDLER_H


#include <QThread>
#include <QSemaphore>
#include "locomotive.h"
#include <QList>

class ILocoHandler : public QThread {

protected:

    // Indique si la section critique est libre
    static bool isFree;
     static bool sens;
     static int locoPriority;
     // Indique les points de passage de la section critique
    QList<int> criticalSectionPoints = {4, 6, 5, 34, 33, 28};
    // Indique les aiguillages critiques
    QList<int> criticalAig= {3,20};
    int startCS = 6;
    int endCS = 33;
    // Sémaphore pour protéger les aiguillages
     static QSemaphore* mutmut;
     // Sémaphore pour protéger la section critique
     static QSemaphore* busypath;

public:
    Locomotive* locomotive;

    ILocoHandler(){
        locomotive = new Locomotive();
    }

    //! Permet de diriger un aiguillage selon un numéro et une direction
    virtual void setAiguillage(int numAig, int direction) = 0;
    //! Gère l'entrée en section critique
    virtual void criticalSectionStart() = 0;
    //! Gère la sortie de la section critique
    virtual void criticalSectionEnd() = 0;
    //! Override de la méthode run de QThread
    virtual void run() = 0;
    //! Gestion du changement de sens d'une locomotive
    void changeSens(bool newSens) {
        // Si une inversion de sens a lieu
        if(sens != newSens){
            // Inversion de toutes les listes
            std::reverse(criticalSectionPoints.begin(), criticalSectionPoints.end());
            std::reverse(criticalAig.begin(), criticalAig.end());
            // Inversion du parcours de la locomotive
            this->locomotive->inverserSensParcours();
            // Inversion du sens de marche de la locomotive
            this->locomotive->inverserSens();
            sens = !(sens);
        }
    }

    static void setPriority(int p){
        locoPriority = p;
    }

    static int getPriority(){
        return locoPriority;
    }
};
#endif // ILOCOHANDLER_H
