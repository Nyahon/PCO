#ifndef LOCOHANDLER1_H
#define LOCOHANDLER1_H

#include "ilocohandler.h"

class LocoHandler1 : public ILocoHandler
{
public:
    LocoHandler1();

    void setAiguillage(bool isFree, int sens, int numAig );
    void criticalSection( bool isFree  );
    void run();
};

#endif // LOCOHANDLER1_H
