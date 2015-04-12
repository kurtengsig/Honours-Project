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
    ConversationController(controller* c, std::string username, std::string friendUsername,
                           std::string ac, std::string ip, std::string p, std::vector<std::string>* messages);
    void updateIncomingMessage(std::string message);
    std::string getAuthCode();
    void sendMessage(std::string message);
    void checkForMessages(std::string*, int*);
    void passMessage(std::string);
    std::string getMessage();
    std::string sanitize(std::string message);
    void notifyClose();
    std::string getFriendName();
    bool inUse();
    bool hasMessage();
    void reOpenWindow(std::vector<std::string> *messages);

private:
    ConversationWindow* cw;
    controller* cont;
    std::string authCode;
    std::string ipAddress;
    std::string port;
    bool initMessage;
    std::deque<std::string> messages;
    std::string replaceString(std::string message, std::string invalid, std::string replacement);
    bool isInUse;
};

#endif // CONVERSATIONCONTROLLER_H
