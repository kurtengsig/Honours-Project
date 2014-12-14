#ifndef CONVERSATIONCONTROLLER_H
#define CONVERSATIONCONTROLLER_H
#include "conversationwindow.h"
#include <QThread>
#include "controller.h"
class ConversationWindow;
class ConversationController : public QThread{
public:
    ConversationController(controller* c, std::string username, std::string friendUserID, std::string ip, std::string port);
    void updateIncomingMessage(std::string message);
    std::string getAuthCode();
    void sendMessage(std::string ip, std::string port, std::string ac, std::string message);

private:
    ConversationWindow* cw;
    controller* cont;
    std::string authCode;
    std::string ip;
    std::string port;
};

#endif // CONVERSATIONCONTROLLER_H
