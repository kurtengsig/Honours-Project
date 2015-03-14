#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "loginwindow.h"
#include "friendwindow.h"
#include <QApplication>
#include <iostream>
#include "encoder.h"
#include "conversationcontroller.h"
#include "serverconnection.h"
#include "registerdialog.h"
#include <QDebug>
#include <vector>
#include "peerconnectionsender.h"
#include <thread>
#include "peerconnectionlistener.h"
#include "conversationcontroller.h"

class ConversationController;
class RegisterDialog;
class LoginWindow;
class FriendWindow;
class controller{
public:
    controller();
    void notifyLoginSubmission(std::string username, std::string password);
    void notifyLogoutRequest();
    void notifyAddFriendRequest(std::string username);
    void notifyConversationCreation(std::string friendName);
    void notifyRegistrationRequest();
    void notifyRegistrationSubmission(std::string username, std::string password);
    void generateKeyAndCert();
    bool handleNewMessage(std::string message);
    void sendInitialMessage(std::string ip, std::string port, std::string ac, std::string message);
    void sendGeneralMessage(std::string ip, std::string port, std::string ac, std::string message);
    void getMessage(std::string* output, int* size);
private:
    std::string myUserName;
    std::string myPassword;
    LoginWindow* w;
    FriendWindow *f;
    RegisterDialog *d;
    std::string ip;
    std::string port;
    ConversationController* convoCont;
    void setIpAndPort();
    bool validInput(std::string input, std::string* output);
    void createFriendWindow(std::string *input, int size);
    std::vector<ConversationController *> currentConversations;
    std::string authCodeReq(std::string friendName);
    void setUsernameAndPass(std::string un, std::string pass);
};

#endif // CONTROLLER_H
