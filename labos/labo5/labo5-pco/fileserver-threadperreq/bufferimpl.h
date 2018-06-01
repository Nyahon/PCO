#ifndef BUFFERIMPL_H
#define BUFFERIMPL_H
#include<QSemaphore>
#include "abstractbuffer.h"
#include <QDebug>
#include "iostream"

template<typename T>
class bufferImpl : public AbstractBuffer<T>
{
protected:
    T *elements;
    int writePointer, readPointer, nbElements, bufferSize;
    QSemaphore mutex, waitProd, waitConso;
    unsigned nbWaitingProd, nbWaitingConso;
public:
    bufferImpl(unsigned int size){
        mutex.release();
        if ((elements = new T[size]) != 0) {
            writePointer = readPointer = nbElements = 0;
            nbWaitingProd = nbWaitingConso = 0;
            bufferSize = size;
            qDebug() << "CREATING buffer";
            return;

        }
        // Exception
        qDebug() << "ERROR CREATING buffer";


    }
    void put(T item)  {

        mutex.acquire();
        // Si le buffer est plein
        if (nbElements == bufferSize) {
            qDebug() << "buffer plein";

            // Un producteur supplémentaire en attente
            nbWaitingProd += 1;
            mutex.release();
            // Producteur en attente
            waitProd.acquire();
        }
        // Remplisage du buffer
        elements[writePointer] = item;
        qDebug() << "élément écrit dans tableau";

        // Avance d'une case dans le buffer
        writePointer = (writePointer + 1) % bufferSize;
        // Ajout d'un élément
        nbElements ++;
        // Si consommateur en attente
        if (nbWaitingConso > 0) {
            // On en relâche un consommateur
            nbWaitingConso -= 1;
            waitConso.release();
        }
        else {
            mutex.release();
        }
    }

    T get(void) {
        qDebug() << "start get";

        T item;
        mutex.acquire();
        // Si le buffer est vide
        if (nbElements == 0) {
            // Consommateur en attente
            nbWaitingConso += 1;
            mutex.release();

            waitConso.acquire();
        }
        // Récupération de l'élément le plus vieux
        item = elements[readPointer];
        readPointer = (readPointer + 1) % bufferSize;
        nbElements --;
        // S'il y a des producteurs en attente
        if (nbWaitingProd > 0) {
            // On en relâche un
            nbWaitingProd -= 1;
            waitProd.release();
        }
        else {
            mutex.release();

        }
        qDebug() << "end get";

        return item;
    }

    int getSize(){
        return bufferSize;
    }

    virtual ~bufferImpl() {}

};


#endif // BUFFERIMPL_H
