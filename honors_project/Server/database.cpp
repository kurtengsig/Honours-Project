#include "database.h"
#include <QSqlError>

database::database(){
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("database.db3");
    db.open();
    QSqlQuery query;
    query.exec("SELECT MAX('userID') FROM Users");
    query.next();
    currentUserNumber = query.value(0).toInt() + 1;
    query.exec("SELECT MAX('friendNumber') FROM Friends");
    query.next();
    currentFriendNumber = query.value(0).toInt() + 1;
}
bool database::loginReq(std::string username, std::string password, std::string ip, std::string port, std::string **output, int *num){
    QSqlQuery query;
    std::string pass;
    PasswordManager p;
    pass = p.hashPassword(password);
    query.exec(("SELECT userID FROM Users WHERE Users.username == '"+username+"'AND Users.password == '"+pass+"'").c_str());
    if(query.isActive() && query.next()){
        std::string uid = query.value(0).toString().toStdString();
        query.exec(("UPDATE Users SET status = 'Online', ipaddress = '"+ip+"',port = '"+port+"' WHERE Users.username =='"+username+"'").c_str());
        int n;
        std::string* out;
        if(friendsListReq(username, &out, &n)){
            std::string* temp = new std::string[3 + n];
            std::ostringstream convert;
            convert << n;
            temp[0] = "1";
            temp[1] = uid;
            temp[2] = convert.str();
            for(int i=0; i < n; i++){
                temp[i+3] = out[i];
            }
            (*output) = temp;

            (*num) = n+3;
            return true;
        }
        std::string* temp = new std::string[2];
        temp[0] = "1";
        temp[1] = "No friends found";
        (*output) = temp;
        (*num) = 2;
        std::cout << "about to return\n";
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
        *output = "Invalid user";
        return false;
    }
    std::ostringstream oss;
    oss << currentUserNumber;

    PasswordManager p;
    std::string pass = p.hashPassword(password);
    query.exec(("INSERT INTO Users VALUES('"+username+"','"+pass+"',"+oss.str()+",'0','0','0','Offline')").c_str());
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
    query.exec(("SELECT ipaddress, port FROM Users WHERE Users.userID = '"+username+"'").c_str());
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
//UNTESTED BEWARE!
bool database::addFriendReq(std::string userID, std::string friendUsername){
    QSqlQuery query;
    std::string init;
    std::string recipient;
    query.exec(("SELECT userID FROM Users WHERE userID = '"+userID+"'").c_str());
    if(!query.isActive())
        return false;
    query.exec(("SELECT userID FROM Users WHERE username = '"+friendUsername+"'").c_str());
    if(!query.isActive())
        return false;
    query.next();
    recipient = query.value(0).toString().toStdString();
    std::ostringstream oss;
    oss << currentFriendNumber;
    return query.exec(("INSERT INTO Friends VALUES("+oss.str()+",'"+userID+"','"+recipient+"'").c_str());
}
void database::miscReq(std::string s){
    QSqlQuery query;
    query.exec(s.c_str());
    if(query.isActive()){
        query.next();
        qDebug() << query.value(0).toString().toStdString().c_str();
        qDebug() << query.value(1).toString().toStdString().c_str();
    }
}
