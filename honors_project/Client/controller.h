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
    bool checkForConnection(std::string message);
    void sendMessage(std::string ip, std::string port, std::string ac, std::string message);
private:
    std::string myUserName;
    std::string myUserID;
    LoginWindow* w;
    FriendWindow *f;
    RegisterDialog *d;
    std::string ip;
    std::string port;
    void setIpAndPort();
    bool validInput(std::string input, std::string* output);
    void createFriendWindow(std::string *input, int size);
    std::vector<ConversationController *> currentConversations;
};

#endif // CONTROLLER_H
