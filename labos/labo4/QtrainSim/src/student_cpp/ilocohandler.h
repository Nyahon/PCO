#ifndef ILOCOHANDLER_H
#define ILOCOHANDLER_H

interface ILocoHandler(){

private:

    bool isFree;
    bool sens;
    int startCS = 6;
    int endCS = 33;
    QSemaphore* mutmut;
    Qsemaphore* busypath;

public:
    virtual void setAiguillage(bool isFree, int sens, int numAig );
    virtual void criticalSection(  );

}
#endif // ILOCOHANDLER_H
