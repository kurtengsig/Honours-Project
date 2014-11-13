#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "loginwindow.h"
#include "friendwindow.h"
#include <QApplication>
#include <iostream>
#include "network.h"
#include "encoder.h"
class LoginWindow;
class FriendWindow;
class controller{
public:
    controller();
    void notifyLoginSubmission(std::string username, std::string password);
    void notifyLogoutRequest();
private:
        network connection;
        LoginWindow* w;
        FriendWindow *f;
        bool validInput(std::string input, std::string* output);
        void createFriendWindow();
};

#endif // CONTROLLER_H
