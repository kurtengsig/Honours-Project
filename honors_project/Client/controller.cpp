#include "controller.h"

controller::controller(){
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
    PeerConnectionListener p(this);
    std::thread server (&PeerConnectionListener::run, &p, 8001);
    server.detach();
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
    qDebug() << "response: " << response.c_str() << "\n";
    cw = new ConversationController(this, myUserName, friendName, "0", "0");
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
        generateKeyAndCert();
        createFriendWindow(temp, size-3);
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

    EVP_PKEY * pkey; //Used for creating the private key object
    pkey = EVP_PKEY_new();

    RSA * rsa; //Generates the private key using RSA
    rsa = RSA_generate_key(2048, RSA_F4, NULL, NULL);

    EVP_PKEY_assign_RSA(pkey, rsa);

    X509 * x509; //Certificate object
    x509 = X509_new();

    ASN1_INTEGER_set(X509_get_serialNumber(x509), 1);

    X509_gmtime_adj(X509_get_notBefore(x509), 0); //Setting certificate duration (1 year)
    X509_gmtime_adj(X509_get_notAfter(x509), 31536000L);

    X509_set_pubkey(x509, pkey); //Sets the public key for the cert

    X509_NAME * name;
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
    system("chmod 600 key.pem");

}
bool controller::checkForConnection(std::string message){
    //HANDLE INCOMING MESSAGE
    for(int i=0; i<currentConversations.size(); ++i){
        if(currentConversations[i]->getAuthCode() == ""){
            currentConversations[i]->updateIncomingMessage(message);
        }
    }
}
void controller::sendMessage(std::string ip, std::string port, std::string ac, std::string message){
    PeerConnectionSender *p;
    //p->sendMessage(ip, port, ac, message);
    qDebug() << "sending" << message.c_str();
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
