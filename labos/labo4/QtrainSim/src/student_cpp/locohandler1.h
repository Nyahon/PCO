#ifndef LOCOHANDLER1_H
#define LOCOHANDLER1_H

#define CS_ENTRY checkPoints.at(0)
#define CS_EXIT checkPoints.at(1)
#define ES_EXIT evCheckPoints.at(0)
#include "ilocohandler.h"

class LocoHandler1 : public ILocoHandler
{
private:
    QList<int> checkPoints{4, 34, 5, 28};
    QList<int> evCheckPoints{29,3};
    QList<int> evitmentAig{4,19};



public:

    void setAiguillage(int numAig, int direction );
    void criticalSectionStart();
    void criticalSectionEnd();
    void evitmentSectionStart();
    void evitmentSectionEnd();
    void changeSens(bool newSens);

    void run();
};

#endif // LOCOHANDLER1_H
