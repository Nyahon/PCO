#ifndef LOCOHANDLER1_H
#define LOCOHANDLER1_H

#define CS_ENTRY checkPoints.at(0)
#define CS_EXIT checkPoints.at(1)

#include "ilocohandler.h"

class LocoHandler1 : public ILocoHandler
{
private:
    QList<int> checkPoints{4, 34, 5, 28};

public:
   // LocoHandler1();

    void setAiguillage(int numAig, int direction );
    void criticalSectionStart();
    void criticalSectionEnd();
    void run();
};

#endif // LOCOHANDLER1_H
