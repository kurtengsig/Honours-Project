#include "conversationcontroller.h"

ConversationController::ConversationController(controller *c, std::string username, std::string friendUsername, std::string ip, std::string port){
    cw = new ConversationWindow(this, username, friendUsername);
    cw->show();
    cont = c;

}
void ConversationController::updateIncomingMessage(std::string message){
    cw->addTheirMessage(message);
}
std::string ConversationController::getAuthCode(){
    return authCode;
}
void ConversationController::sendMessage(std::string ip, std::string port, std::string ac, std::string message){
    cont->sendMessage(ip, port, ac, message);
}
