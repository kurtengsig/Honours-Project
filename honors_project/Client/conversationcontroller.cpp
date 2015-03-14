#include "conversationcontroller.h"

ConversationController::ConversationController(controller *c){
    cont = c;
    initMessage = true;
    cw = new ConversationWindow(this);
}
ConversationController::ConversationController(controller* c, std::string username, std::string friendUsername, std::string ac, std::string ip, std::string p){
    authCode = ac;
    ipAddress = ip;
    port = p;
    cont = c;
    initMessage = true;
    cw = new ConversationWindow(this);
    cw->setUserAndFriend(username, friendUsername);
    //cw->show();
}

/*void ConversationController::updateIncomingMessage(std::string message){
    cw->addMessage(message);
}*/
std::string ConversationController::getAuthCode(){
    qDebug() << "getting authCode";
    return authCode;
}
void ConversationController::sendMessage(std::string message){
    cont->sendInitialMessage(ipAddress,port,authCode,message);
}
void ConversationController::updateIncomingMessage(std::string message){
    messages.push_back(message);
    for(int i=0; i< messages.size(); i++){
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
bool ConversationController::haveMessage(){
    if(messages.size() > 0)
        return true;
    return false;
}
