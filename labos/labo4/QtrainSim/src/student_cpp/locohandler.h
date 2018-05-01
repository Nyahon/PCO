#ifndef LOCOHANDLER
#define LOCOHANDLER
#include <QThread>
#include "locomotive.h"
class LocoHandler : public QThread{
public:
    Locomotive locomotive;

    LocoHandler();
    //! implementation QThread
    void run();
private:
    int priorite;
};

#endif // LOCOHANDLER

