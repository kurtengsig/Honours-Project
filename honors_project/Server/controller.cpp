#include "controller.h"

Controller::Controller(){
    d = new database();
    e = new encoder();
    while(1){
        c->run(8000, d);
        //delete(c);
    }
}
