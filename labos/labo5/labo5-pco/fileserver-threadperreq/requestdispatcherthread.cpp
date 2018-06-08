#include "requestdispatcherthread.h"
#include <QDebug>

void requestDispatcherThread::run()
{

    while(true) {

        //suppress loop for running threads with no charge
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
      //  RunnableImpl* runnable = new RunnableImpl(rw);

        procList.push_back(rw);
        //rw->start();


        //responseReady(resp); // send signal
    }
}
