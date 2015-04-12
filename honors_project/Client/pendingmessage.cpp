#include "pendingmessage.h"

PendingMessage::PendingMessage(std::string f, std::string m){
    origin = f;
    message = m;
}
std::string PendingMessage::getOrigin(){
    return origin;
}

std::string PendingMessage::getMessage(){
    return message;
}
