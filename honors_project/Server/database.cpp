#include "database.h"
#include <QSqlError>
#include <string>

database::database(){
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("hp.db3");
    db.open();
    QSqlQuery query;
    query.exec("SELECT MAX(userID) FROM Users");
    query.next();
    currentUserNumber = query.value(0).toInt() + 1;
    query.exec("SELECT MAX(friendNumber) FROM Friends");
    query.next();
    currentFriendNumber = query.value(0).toInt() + 1;
}
bool database::loginReq(std::string username, std::string password, std::string ip, std::string port, std::string **output, int *num){
    QSqlQuery query;
    std::string pass;
    std::string salt ="";
    query.exec(("SELECT salt FROM Users WHERE Users.username == '"+username+"'").c_str());
    if(query.isActive()){
        query.next();
        salt = query.value(0).toString().toStdString();
    }
    pass = hashPassword(password, salt);
    query.exec(("SELECT userID FROM Users WHERE Users.username == '"+username+"'AND Users.password == '"+pass+"'").c_str());
    if(query.isActive() && query.next()){
        std::string uid = query.value(0).toString().toStdString();
        query.exec(("UPDATE Users SET status = 'Online', ipaddress = '"+ip+"',port = '"+port+"' WHERE Users.username =='"+username+"'").c_str());
        int n;
        std::string* out;
        if(friendsListReq(username, &out, &n)){
            std::string* temp = new std::string[2 + n];
            std::ostringstream convert;
            convert << n;
            temp[0] = "1";
            temp[1] = convert.str();
            for(int i=0; i < n; i++){
                temp[i+2] = out[i];
            }
            (*output) = temp;

            (*num) = n+2;
            return true;
        }
        std::string* temp = new std::string[2];
        temp[0] = "1";
        temp[1] = "No friends found";
        (*output) = temp;
        (*num) = 2;
        return false;
    }
    qDebug() << query.lastError();
    std::string* temp = new std::string[2];
    temp[0] = "-1";
    temp[1] = "Invalid username or password";
    (*num) = 2;
    (*output) = temp;
    return false;

}
bool database::logoutReq(std::string username){
    QSqlQuery query;
    return query.exec(("UPDATE Users SET status = 'Offline' WHERE Users.username == '"+username+"'").c_str());
}
bool database::registerUserReq(std::string username, std::string password, std::string* output){
    QSqlQuery query;
    query.exec(("SELECT userID FROM Users WHERE Users.username == "+username).c_str());
    if(query.isActive()){
        query.next();
        *output = "Invalid";
        return false;
    }
    std::ostringstream oss;
    oss << currentUserNumber;
    std::string salt = getSalt();
    std::string pass = hashPassword(password, salt);
    query.exec(("INSERT INTO Users VALUES('"+username+"','"+pass+"','"+salt+"',"+oss.str()+",'0','0','0','Offline')").c_str());
    query.exec(("SELECT username FROM Users WHERE Users.username =="+username).c_str());
    if(query.isActive()){
        query.next();
        qDebug() << query.value(0);
    }
    qDebug() << query.lastError();
    *output = "Successfully added new user";
    return true;
}
bool database::friendsListReq(std::string username, std::string** output, int* n){
    QSqlQuery query;
    query.exec(("SELECT userID FROM Users WHERE Users.username =='"+username+"'").c_str());
    if(query.isActive()){
        query.next();
        QSqlQuery secondQuery;
        secondQuery.exec(("SELECT * FROM Users INNER JOIN Friends ON Users.userID == Friends.friendID WHERE Users.status == 'Online' AND Friends.userID =='"+query.value(0).toString().toStdString()+"'").c_str());
        if(secondQuery.isActive()){
            secondQuery.last();
            int size = secondQuery.at()+1;
            secondQuery.first();
            if(size < 0)
                size = 0;
            *n = size;
            std::string* temp = new std::string[size];
            for(int i=0; i<size; i++){
                temp[i] = secondQuery.value(0).toString().toStdString();
                secondQuery.next();
            }
            *output = temp;
            return true;
        }
    }
    qDebug() << "NOT ACTIVE";
    std::string* temp = new std::string[1];
    temp[0] = "No friends exist";
    *n =1;
    *output = temp;
    return false;
}
bool database::contactInfoReq(std::string username, std::string** output, int* n){
    QSqlQuery query;
    query.exec(("SELECT ipaddress, port FROM Users WHERE Users.username = '"+username+"'").c_str());
    if(query.isActive() && query.next()){
        std::string* temp = new std::string[2];
        temp[0] = query.value(0).toString().toStdString();
        temp[1] = query.value(1).toString().toStdString();
        *output = temp;
        *n = 2;
        return true;
    }
    *n = 1;
    std::string* temp = new std::string[1];
    temp[0] = "Error this user does not exist";
    *output = temp;
    return false;
}
std::string database::addFriendReq(std::string username, std::string friendUsername){
    QSqlQuery query;
    std::string init;
    std::string recipient;
    query.exec(("SELECT userID FROM Users WHERE username = '"+username+"'").c_str());
    if(!query.isActive())
        return "Invalid";
    query.next();
    init = query.value(0).toString().toStdString();
    query.exec(("SELECT userID FROM Users WHERE username = '"+friendUsername+"'").c_str());
    if(!query.isActive())
        return "Invalid";
    query.next();
    recipient = query.value(0).toString().toStdString();
    std::ostringstream oss;
    oss << currentFriendNumber;
    std::ostringstream oss2;
    oss2 << (currentFriendNumber+1);
    qDebug() << "query" << ("INSERT INTO Friends VALUES("+oss.str()+",'"+init+"','"+recipient+"')").c_str();
    std::string salt = getSalt();
    if((query.exec(("INSERT INTO Friends VALUES("+oss.str()+",'"+init+"','"+recipient+"','"+salt+"')").c_str())) &&
            (query.exec(("INSERT INTO Friends VALUES("+oss2.str()+",'"+recipient+"','"+init+"','"+salt+"')").c_str()))   ){
        currentFriendNumber +=2;
        return "Succesfully added";
    }
    qDebug() << query.lastError();
    return "Invalid";
}
std::string database::getAuthenticationCode(std::string username1, std::string password, std::string username2){
    if(verifyUser(username1, password)){
        QSqlQuery query;
        QSqlQuery query2;
        std::string output;
        query.exec(("SELECT userID FROM Users WHERE Users.username == '"+username1+"' OR Users.username == '"+username2+"'").c_str());
        if(query.isActive()){
            query.last();
            int size = query.at()+1;
            if(size != 2) return "Invalid";
            query.first();
            int item1 = atoi(query.value(0).toString().toStdString().c_str());
            query.next();
            int item2 = atoi(query.value(0).toString().toStdString().c_str());
            if(item1 > item2){
                output = std::to_string(item2)+""+std::to_string(item1);
            }
            else{
                output = std::to_string(item1)+""+std::to_string(item2);
            }
            query2.exec(("SELECT salt FROM Friends WHERE userID == '"+std::to_string(item1)+"' AND friendID == '"+std::to_string(item2)+"'").c_str());
            std::string salt = "";
            if(query2.isActive()){
                query2.next();
                salt = query2.value(0).toString().toStdString();
            }
            output = hashPassword(output, salt);
            return output;
        }
    }
    return "Invalid";
}
void database::miscReq(std::string s){
    QSqlQuery query;
    query.exec(s.c_str());
    if(query.isActive()){
        query.next();
        qDebug() << query.value(0).toString().toStdString().c_str();
    }
}
bool database::verifyUser(std::string username, std::string password){
    QSqlQuery query;
    std::string salt = "";
    query.exec(("Select salt FROM Users WHERE Users.username == '"+username+"'").c_str());
    if(query.isActive()){
        query.next();
        salt = query.value(0).toString().toStdString();
    }
    query.clear();
    std::string pass;
    pass = hashPassword(password, salt);
    query.exec(("SELECT userID FROM Users WHERE Users.username == '"+username+"'AND Users.password == '"+pass+"'").c_str());
    if(query.isActive() && query.next()){
        return true;
    }
    return false;
}
std::string database::hashPassword(std::string password, std::string salt){
    std::string p = password+""+salt;
    byte const* pass = (byte*) p.data();
    unsigned int nDataLen = p.size();
    byte digest[CryptoPP::SHA256::DIGESTSIZE];

    CryptoPP::SHA256().CalculateDigest(digest, pass, nDataLen);

    CryptoPP::HexEncoder enc;
    std::string output;
    enc.Put(digest, sizeof(digest));
    enc.MessageEnd();

    CryptoPP::word64 size = enc.MaxRetrievable();
    if(size){
        output.resize(size);
        enc.Get((byte*)output.data(), output.size());
    }
    return output;
}

std::string database::getSalt(){
    CryptoPP::AutoSeededRandomPool rng;
    const unsigned int BLOCKSIZE = 8 * 8;
    byte random[BLOCKSIZE];
    rng.GenerateBlock(random, BLOCKSIZE );


    CryptoPP::HexEncoder enc;
    std::string output;
    enc.Put(random, sizeof(random));
    enc.MessageEnd();

    CryptoPP::word64 size = enc.MaxRetrievable();
    if(size){
        output.resize(size);
        enc.Get((byte*)output.data(), output.size());
    }
    return output;
}
