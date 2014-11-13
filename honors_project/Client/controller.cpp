#include "controller.h"

controller::controller(){
    connection.create();
    w = new LoginWindow(this);
    w->show();
}
void controller::notifyLoginSubmission(std::string username, std::string password){
    std::string error;
    if(!validInput(username, &error)){
        w->setErrorMessage(error);
        return;
    }
    if(!validInput(password, &error)){
        w->setErrorMessage(error);
        return;
    }
    w->setErrorMessage("");
    std::string message;
    std::string input[3] = {"LIR", username, password};
    encoder e;
    message = e.encode(input, 3);
    connection.sendMessage(message);
    std::cout << "Login message sent!"<<std::endl;
    w->hide();
    delete(w);
    createFriendWindow();
}
bool controller::validInput(std::string input, std::string* output){
    if((input.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-_") != std::string::npos) || input == ""){
        *output = "Invalid Username or Password\nmay only contain letters, numbers, '-' and '_'";
        return false;
    }
    *output = "valid";
    return true;
}
void controller::notifyLogoutRequest(){
    encoder e;
    std::string input[2] = {"LOR", "username"};
    std::string message = e.encode(input, 2);
    connection.sendMessage(message);
    std::cout << "Logout message sent!"<<std::endl;
}
void controller::createFriendWindow(){
    f = new FriendWindow(this);
    f->show();
}
