#include "conversationcontroller.h"

ConversationController::ConversationController(int convoId, std::string friendUsername, std::string ip, std::string port){
    cw = new ConversationWindow(friendUsername);
    cw->show();
    conversationID = convoId;
}
void ConversationController::updateIncomingMessage(std::string message){
    cw->addNewMessage("",message);
}
