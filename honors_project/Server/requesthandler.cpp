#include "requesthandler.h"

RequestHandler::RequestHandler(){

}
std::string RequestHandler::handle(std::string input, database *d){
    e = new encoder();
    e->decode(&values, &size, input);
    if(values[0] == "LIR" && size == 5){
        std::string* output;
        int num;
        if(d->loginReq(values[1], values[2], values[3], values[4], &output, &num)){
            return e->encode(output, num);
        }
        else{
            return e->encode(output, 2);
        }
    }
    if(values[0] == "LOR"){
        if(d->logoutReq(values[1])){
            std::string input[2] = {"1", "Success"};
            return e->encode(input, 2);
        }
        return "logout failed";
    }
    if(values[0] == "PIR"){
        std::string* output;
        int size;
        d->contactInfoReq(values[1], &output, &size);
        return e->encode(output, size);
    }
    if(values[0] == "AFR"){
        //return d->addFriendReq(values[1], values[2]);
    }
    if(values[0] == "RUR"){
        return "Register user request";
    }
    return "Unknown request";
}