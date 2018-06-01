#include "requestworker.h"
#include "requesthandler.h"

void requestWorker::run(){
    // creating the request handler
    RequestHandler handle = RequestHandler(r, true);

    // handling the request
    Response response = handle.handle();

    // push the response to the response buffer
    buff->put(response);
    

}
