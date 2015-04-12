#include "controller.h"

controller::controller(){
    myUserName = "";
    myPassword = "";
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
    PeerConnectionListener* p = new PeerConnectionListener(this);
    std::thread server(&PeerConnectionListener::run, p, atoi(port.c_str()));
    server.detach();
    f = new FriendWindow(this);
    f->populateFriendList(input, size);
    f->show();
}
void controller::notifyAddFriendRequest(std::string username){
    ServerConnection s;
    encoder e;
    std::string input[4] = {"AFR", myUserName, myPassword, username};
    std::string message = e.encode(input, 4);
    std::cout << s.sendMessage(message) << "\n";
}
void controller::notifyConversationCreation(std::string friendName){
    ConversationController* cc;
    ServerConnection s;
    encoder e;
    std::string input[4] = {"PIR", myUserName, myPassword, friendName};
    std::string message = e.encode(input, 4);
    std::string response = s.sendMessage(message);
    std::string* output;
    int size;
    e.decode(&output, &size, response); // gets username ip (0) and port (1)

    //Fetches the authentication code from the server
    std::string authenticationCode = authCodeReq(friendName);

    if(size == 2 && authenticationCode != "Invalid"){

        std::vector<std::string> messages;
        std::vector<PendingMessage> newPending;

        for(int i=0; i<pendingMessages.size(); i++){
            if(pendingMessages.at(i).getOrigin() == friendName){
                messages.push_back(pendingMessages.at(i).getMessage());
            }
            else{
                newPending.push_back(pendingMessages.at(i));
            }
        }
        pendingMessages = newPending;

        //Case of a message coming to an existing controller
        for(int i=0; i< currentConversations.size(); i++){
            if(authenticationCode == currentConversations.at(i)->getAuthCode()){
                currentConversations.at(i)->reOpenWindow(&messages);
                return;
            }
        }

        cc = new ConversationController(this, myUserName, friendName,authenticationCode ,output[0], output[1], &messages); //add pending messages here
        currentConversations.push_back(cc);
    }
}
void controller::notifyLoginSubmission(std::string username, std::string password){
    std::string error;
    if(!validInput(username, &error) || !validInput(password, &error)){
        w->setErrorMessage(error);
        return;
    }
    setIpAndPort();
    w->setErrorMessage("");
    std::string message;
    std::string input[5] = {"LIR", username, password, ip, port};
    encoder e;
    message = e.encode(input, 5);
    ServerConnection serve;
    std::string response = serve.sendMessage(message);
    qDebug() << "Received: "<<response.c_str();
    std::string* output;
    int size;
    e.decode(&output, &size, response);
    if(output[0] == "1" && size >= 2 ){ // Success
        setUsernameAndPass(username, password);
        w->hide();
        delete(w);
        //The first 2 values of the response are the code and number of friends, the rest are friend usernames
        std::string* temp = new std::string[size-2];
        for(int i=2; i<size; i++){
            temp[i-2] = output [i];
        }
        generateKeyAndCert();
        createFriendWindow(temp, size-2);
    }
    else if(output[0] ==  "0"){ // Successful login but no friends
        generateKeyAndCert();
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

void controller::notifyRegistrationRequest(){
    d = new RegisterDialog(this);
    d->setVisible(true);
}
void controller::notifyRegistrationSubmission(std::string username, std::string password){
    encoder e;
    std::string input[3] = {"RUR", username, password};
    std::string message = e.encode(input, 3);
    qDebug() << message.c_str();
    ServerConnection n;
    message = n.sendMessage(message);
    w->setErrorMessage(message);
}
void controller::generateKeyAndCert(){

    EVP_PKEY* pkey; //Used for creating the private key object
    pkey = EVP_PKEY_new();

    RSA* rsa; //Generates the private key using RSA
    rsa = RSA_generate_key(2048, RSA_F4, NULL, NULL);

    EVP_PKEY_assign_RSA(pkey, rsa);

    X509* x509; //Certificate object
    x509 = X509_new();

    ASN1_INTEGER_set(X509_get_serialNumber(x509), 1);

    X509_gmtime_adj(X509_get_notBefore(x509), 0); //Setting certificate duration (1 year)
    X509_gmtime_adj(X509_get_notAfter(x509), 31536000L);

    X509_set_pubkey(x509, pkey); //Sets the public key for the cert

    X509_NAME* name;
    name = X509_get_subject_name(x509);

    std::string s = "Peer to peer IM -user"+myUserName;

    //The following sets the required fields for the cert (Country, Organisation, Common Name)
    X509_NAME_add_entry_by_txt(name, "C", MBSTRING_ASC, (unsigned char *)"CA", -1, -1, 0);
    X509_NAME_add_entry_by_txt(name, "O", MBSTRING_ASC, (unsigned char *)"Honours project", -1, -1, 0);
    X509_NAME_add_entry_by_txt(name, "CN", MBSTRING_ASC, (unsigned char *)s.c_str(), -1, -1, 0);

    X509_set_issuer_name(x509, name);
    X509_sign(x509, pkey, EVP_sha256());

    //Saves the certificate and file to their own file
    FILE *f;
    f = fopen("key.pem", "wb");
    PEM_write_PrivateKey(f, pkey, NULL, NULL, 0, NULL, NULL);
    fclose(f);
    f = fopen("cert.pem", "wb");
    PEM_write_X509(f, x509);
    fclose(f);
    //system("chmod 600 key.pem");

}
void controller::handleNewMessage(std::string message){
    encoder e;
    std::string* output;
    int size;
    e.decode(&output, &size, message);
    qDebug() << currentConversations.size();
    //Check if the conversation exists
    for(unsigned int i=0; i<currentConversations.size(); ++i){
        if((currentConversations[i]->getAuthCode() == output[1]) && currentConversations[i]->inUse()){
            qDebug() << "in use";
            currentConversations[i]->updateIncomingMessage(output[2]);
            return;
        }
    }
    // If it doesnt exist, needs to check to see if the person contacting you is a friend of yours
    std::string authCodes = authCodeReq(output[0]);//Gets the authentication code for the user with that username
    if(authCodes == output[1]){ //if the codes are the same, its a valid message
        pendingMessages.push_back(PendingMessage(output[0], output[2]));
    }
    //Otherwise the message is dropped
}
void controller::sendInitialMessage(std::string i, std::string p, std::string ac, std::string message){
    encoder e;
    std::string input[] = {myUserName, ac, message, ip, port};
    std::string newMessage = e.encode(input, 5);
    PeerConnectionSender pcs; // MIGHT NEED TO BE A POINTER
    pcs.sendMessage(i, p, newMessage);// send to ip and port
}

void controller::setIpAndPort(){
    std::ifstream file("myloc.txt");
    if(file.is_open()){
        getline(file, ip);
        getline(file, port);
    }
    else{
        ip = "-1";
        port = "-1";
    }
}

//This function gets the authorization code for the current user and the provided username
std::string controller::authCodeReq(std::string friendName){
    ServerConnection s;
    encoder en;
    std::string input[] = {"ACR", myUserName, myPassword, friendName};
    std::string message = en.encode(input, 4);
    std::string response = s.sendMessage(message);
    return response;
}
void controller::setUsernameAndPass(std::string un, std::string pass){
    myUserName = un;
    myPassword = pass;
}
int controller::getPendingMessages(PendingMessage** m){
    if(pendingMessages.size() > 0){
        *m = &pendingMessages[0];
        return pendingMessages.size();
    }
    return 0;
}
