#ifndef LOCOHANDLER2_H
#define LOCOHANDLER2_H

#define CS_ENTRY checkPoints.at(0)
#define CS_EXIT checkPoints.at(1)


#include "ctrain_handler.h"
#include "locomotive.h"
#include "ilocohandler.h"
#include <QThread>
#include <QSemaphore>
class LocoHandler2 : public ILocoHandler {
private:
    QList<int> checkPoints{8, 34, 5, 36};
public:

    void setAiguillage(int numAig, int direction);
    void criticalSectionStart();
    void criticalSectionEnd();
    void run();
    void changeSens(bool newSens);
};
#endif // LOCOHANDLER2_H
