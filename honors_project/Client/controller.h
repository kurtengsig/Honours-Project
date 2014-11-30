#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "loginwindow.h"
#include "friendwindow.h"
#include <QApplication>
#include <iostream>
#include "network.h"
#include "encoder.h"
#include"conversationcontroller.h"
#include "serverconnection.h"
class LoginWindow;
class FriendWindow;
class controller{
public:
    controller();
    void notifyLoginSubmission(std::string username, std::string password);
    void notifyLogoutRequest();
    void notifyAddFriendRequest(std::string username);
    void notifyConversationCreation(std::string friendName);
private:
    std::string myUserName;
    std::string myUserID;
    network connection;
    LoginWindow* w;
    FriendWindow *f;
    bool validInput(std::string input, std::string* output);
    void createFriendWindow(std::string *input, int size);
};

#endif // CONTROLLER_H
