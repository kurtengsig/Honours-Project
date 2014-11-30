#ifndef CONVERSATIONCONTROLLER_H
#define CONVERSATIONCONTROLLER_H
#include "conversationwindow.h"

class ConversationController{
public:
    ConversationController(int convoId, std::string friendUserID, std::string ip, std::string port);
    void updateIncomingMessage(std::string message);

private:
    ConversationWindow* cw;
    int conversationID;
};

#endif // CONVERSATIONCONTROLLER_H
