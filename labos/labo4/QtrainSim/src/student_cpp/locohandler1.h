#ifndef LOCOHANDLER1_H
#define LOCOHANDLER1_H

#include "ilocohandler.h"

class LocoHandler1 : public ILocoHandler
{
public:
    LocoHandler1();

    void setAiguillage(int numAig, int direction );
    void criticalSectionStart();
    void criticalSectionEnd();
    void run();
};

#endif // LOCOHANDLER1_H
