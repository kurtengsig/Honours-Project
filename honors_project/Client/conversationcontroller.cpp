#include "conversationcontroller.h"

ConversationController::ConversationController(controller *c){
    cont = c;
    initMessage = true;
    cw = new ConversationWindow(this);
}
ConversationController::ConversationController(controller* c, std::string username, std::string friendUsername,
                                               std::string ac, std::string ip, std::string p, std::vector<std::string> *messages) : isInUse(true){
    authCode = ac;
    ipAddress = ip;
    port = p;
    cont = c;
    initMessage = true;
    cw = new ConversationWindow(this);
    cw->setUserAndFriend(username, friendUsername);
    for(int i=0; i<messages->size(); i++)
        updateIncomingMessage(messages->at(i));
    cw->show();
}

std::string ConversationController::getAuthCode(){
    return authCode;
}
void ConversationController::sendMessage(std::string message){
    cont->sendInitialMessage(ipAddress,port,authCode,message);
}
void ConversationController::updateIncomingMessage(std::string message){
    messages.push_back(message);
    for(unsigned int i=0; i< messages.size(); i++){
        qDebug() <<"have message: " << messages[i].c_str();
    }
}
void ConversationController::passMessage(std::string m){
    messages.push_front(m);
}

std::string ConversationController::getMessage(){
    std::string output = messages.back();
    messages.pop_back();
    return output;
}
std::string ConversationController::sanitize(std::string message){
    std::string invalidStrings[] = {"~", "<", ">"};
    int size = sizeof(invalidStrings) / sizeof(invalidStrings[0]);
    for(int i=0; i<size; i++){
        message = replaceString(message, invalidStrings[i], " ");
    }
    return message;
}
std::string ConversationController::replaceString(std::string message, std::string invalid, std::string replacement){
    if(message.length() == 0 || invalid.length() == 0 || replacement.length() == 0)
        return message;
    size_t pos = 0;
    while((pos = message.find(invalid, pos)) != std::string::npos) {
        message.replace(pos, invalid.length(), replacement);
        pos += replacement.length();
    }
    return message;
}
void ConversationController::notifyClose(){
    //delete(cw);
    isInUse = false;
}
bool ConversationController::inUse(){
    return isInUse;
}
void ConversationController::reOpenWindow(std::vector<std::string>* messages){
    for(int i=0; i<messages->size(); i++)
        updateIncomingMessage(messages->at(i));
    isInUse = true;
    cw->show();
}
bool ConversationController::hasMessage(){
    return !messages.empty();
}
