#include "controller.h"

Controller::Controller(){
    d = new database();
    e = new encoder();
    while(1){
        c = new Connection(d);
        delete(c);
    }
}
