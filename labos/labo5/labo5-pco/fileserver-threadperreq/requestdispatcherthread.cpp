#include "requestdispatcherthread.h"
#include <QDebug>

void requestDispatcherThread::run()
{

    while(true) {

        while(!procList.empty() ){
            qDebug() << "procList not empty";

            requestWorker* rwThread = procList.first();

            if(rwThread->isFinished()){
                procList.pop_front();
                delete rwThread;
            }else{
                break;
            }
        }
        if (hasDebugLog)
            qDebug() << "Waiting for requests...";
        Request req = requests->get();   //  Récupération des requêtes dans le tampon
         // Création d'un worker qui va mettre la requête dans le buffer de réponses
        requestWorker* rw = new requestWorker(req, responses);
        procList.push_back(rw);
        rw->start();
        //responseReady(resp); // send signal
    }
}
