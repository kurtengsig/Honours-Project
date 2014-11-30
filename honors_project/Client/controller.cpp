#include "controller.h"

controller::controller(){
    //connection.create();
    w = new LoginWindow(this);
    w->show();
}
bool controller::validInput(std::string input, std::string* output){
    if((input.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-_") != std::string::npos) || input == ""){
        *output = "Invalid Username or Password\nmay only contain letters, numbers, '-' and '_'";
        return false;
    }
    *output = "valid";
    return true;
}
void controller::createFriendWindow(std::string* input, int size){
    f = new FriendWindow(this);
    f->populateFriendList(input, size);
    f->show();
}
void controller::notifyAddFriendRequest(std::string username){
    ServerConnection s;
    encoder e;
    std::string input[3] = {"AFR", myUserID, username};
    std::string message = e.encode(input, 3);
    std::cout << s.sendMessage(message) << "\n";
}
void controller::notifyConversationCreation(std::string friendName){
    ConversationController* cw;
    ServerConnection s;
    encoder e;
    std::string input[3] = {"PIR", myUserID, friendName};
    std::string message = e.encode(input, 3);
    std::string response = s.sendMessage(message);
    std::cout << response << "\n";
    //cw = new ConversationController(0, friendName, 0, 0);
}
void controller::notifyLoginSubmission(std::string username, std::string password){
    std::string error;
    if(!validInput(username, &error) || !validInput(password, &error)){
        w->setErrorMessage(error);
        return;
    }
    w->setErrorMessage("");
    std::string message;
    std::string input[5] = {"LIR", username, password, "localhost", "8000"};
    encoder e;
    message = e.encode(input, 5);
    ServerConnection serve;
    std::string response = serve.sendMessage(message);
    std::string* output;
    int size;
    e.decode(&output, &size, response);
    if(output[0] == "1"){ // Success
        myUserName = username;
        myUserID = output[1];
        w->hide();
        delete(w);
        std::string* temp = new std::string[size-3];
        for(int i=3; i<size; i++){
            temp[i-3] = output [i];
        }
        createFriendWindow(temp, size-3);
    }
    else if(output[0] ==  "0"){ // Successful login but no friends

    }
    else{ // Failed login
        w->setErrorMessage(output[1]);
    }
}
void controller::notifyLogoutRequest(){
    encoder e;
    std::string input[2] = {"LOR", myUserName};
    std::string message = e.encode(input, 2);
    ServerConnection n;
    n.sendMessage(message);
    std::exit(EXIT_FAILURE);
}
