#ifndef LOCOHANDLER2_H
#define LOCOHANDLER2_H

#define CS_ENTRY checkPoints.at(0)
#define CS_EXIT checkPoints.at(1)


#include "ctrain_handler.h"
#include "locomotive.h"
#include "ilocohandler.h"
#include <QThread>
#include <QSemaphore>

/**
 * @brief The LocoHandler2 class
 * Locomotive n'utilisant *PAS* la voie d'évitement
 */
class LocoHandler2 : public ILocoHandler {
private:
    // Liste des points de passage où un contrôle de section critique doit être effectué
    QList<int> checkPoints{9, 34, 5, 35};
public:
    void setAiguillage(int numAig, int direction);
    void criticalSectionStart();
    void criticalSectionEnd();
    void run();
    //! Redéfinition de la méthode changeSens() de ILocoHandler
    void changeSens(bool newSens);
};
#endif // LOCOHANDLER2_H
