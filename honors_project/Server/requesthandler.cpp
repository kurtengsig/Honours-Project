#include "requesthandler.h"

RequestHandler::RequestHandler(){

}
std::string RequestHandler::handle(std::string input, database *d){
    if(!validInput(input)) return "Invalid";
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
    if(values[0] == "LOR" && size == 2){
        if(d->logoutReq(values[1])){
            std::string input[2] = {"1", "Success"};
            return e->encode(input, 2);
        }
        return "logout failed";
    }
    if(values[0] == "PIR"&& size == 4){
        if(d->verifyUser(values[1], values[2])){
            std::string* output;
            int localSize;
            d->contactInfoReq(values[3], &output, &localSize);
            return e->encode(output, localSize);
    }
    }
    if(values[0] == "AFR" && size == 4){
        if(d->verifyUser(values[1], values[2])){
            return d->addFriendReq(values[1], values[3]);
        }
    }
    if(values[0] == "RUR" && size == 3){
        std::string output;
        d->registerUserReq(values[1], values[2], &output);
        return output;
    }
    if(values[0] == "ACR" && size == 4){
        //                              username,  password,  friend username
        return d->getAuthenticationCode(values[1], values[2], values[3]);
    }
    return "Unknown request";
}
bool RequestHandler::validInput(std::string input){
    if((input.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-_~!") != std::string::npos) || input == ""){
        return false;
    }
    return true;
}
