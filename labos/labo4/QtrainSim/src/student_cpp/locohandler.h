#ifndef LOCOHANDLER
#define LOCOHANDLER
#include <QThread>
#include "locomotive.h"
class LocoHandler : public QThread{
public:
    LocoHandler();
    //! implementation QThread
    void run();
private:
    Locomotive locomotive;
    int priorite;
};

#endif // LOCOHANDLER

