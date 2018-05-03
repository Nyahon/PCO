#ifndef LOCOHANDLER2_H
#define LOCOHANDLER2_H

#include "ctrain_handler.h"
#include "locomotive.h"
#include "ilocohandler.h"
#include <QThread>
#include <QSemaphore>
class LocoHandler2 : public ILocoHandler {

private:


public:
    void setAiguillage(int numAig, int direction);
    void criticalSectionStart();
    void criticalSectionEnd();
    void run();

};
#endif // LOCOHANDLER2_H
