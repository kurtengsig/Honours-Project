#ifndef CONVERSATIONCONTROLLER_H
#define CONVERSATIONCONTROLLER_H
#include "conversationwindow.h"
#include <QThread>
#include "controller.h"
#include <deque>
class ConversationWindow;
class ConversationController : public QThread{
public:
    ConversationController(controller* c);
    ConversationController(controller* c, std::string username, std::string friendUsername, std::string ac, std::string ip, std::string p);
    void updateIncomingMessage(std::string message);
    std::string getAuthCode();
    void sendMessage(std::string message);
    void checkForMessages(std::string*, int*);
    void passMessage(std::string);
    std::string getMessage();
    bool haveMessage();

private:
    ConversationWindow* cw;
    controller* cont;
    std::string authCode;
    std::string ipAddress;
    std::string port;
    bool initMessage;
    std::deque<std::string> messages;
};

#endif // CONVERSATIONCONTROLLER_H
