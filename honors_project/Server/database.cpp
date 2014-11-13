#include "database.h"

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
void database::miscFunction(std::string q){
    QSqlQuery query;
    qDebug() << "About to execute misc function:";
    query.exec(q.c_str());
    if(query.isActive()){
        while(query.next()){
            qDebug() << query.value(0).toString().toStdString().c_str();
        }
    }
}
bool database::loginReq(std::string username, std::string password, std::string* output){
    QSqlQuery query;
    query.exec(("SELECT userID FROM Users WHERE Users.username == '"+username+"'AND Users.password == '"+password+"'").c_str());
    if(!query.isActive()){
        *output = "Failed to login";
        return false;
    }
    query.next();
    *output = query.value(0).toString().toStdString();
    //TODO update the status, check in, ip, port
    query.exec(("UPDATE Users SET status = 'Online' WHERE Users.username =='"+username+"'").c_str());

}
bool database::logoutReq(std::string username){
    QSqlQuery query;
    return query.exec(("UPDATE Users SET status = 'Offline' WHERE Users.username =='"+username+"'").c_str());
}

/* UNTESTED!!! BEWARE !! */
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
    query.exec(("INSERT INTO Users VALUES('"+username+"','"+password+"',"+oss.str()+",'0','0','0','Offline')").c_str());
    query.exec(("SELECT username FROM Users WHERE Users.username =="+username).c_str());
    if(query.isActive()){
        query.next();
        qDebug() << query.value(0);
    }
    *output = "Successfully added new user";
    return true;
}
bool database::friendsListReq(std::string username, std::string** output, int* n){
    QSqlQuery query;
    query.exec(("SELECT userID FROM Users WHERE Users.username =='"+username+"'").c_str());
    if(query.isActive()){
        query.next();
        QSqlQuery secondQuery;
        secondQuery.exec(("SELECT * FROM Users INNER JOIN Friends ON Users.userID==Friends.friendID WHERE Users.status == 'Online' AND Friends.userID =="+query.value(0).toString().toStdString()).c_str());
        secondQuery.last();
        int size = secondQuery.at()+1;
        secondQuery.first();
        *n = size;
        std::string* temp = new std::string[size];
        for(int i=0; i<size; i++){
            temp[i] = secondQuery.value(0).toString().toStdString();
            secondQuery.next();
        }
        *output = temp;
        return true;
    }
    qDebug() << "NOT ACTIVE";
    std::string* temp = new std::string[1];
    temp[0] = "No friends exist";
    *n =1;
    *output = temp;
    return false;
}
bool database::contactInfoReq(std::string username, std::string** output){
    QSqlQuery query;
    query.exec(("SELECT ipaddress, port FROM Users WHERE Users.username='"+username+"'").c_str());
    if(query.isActive()){
        query.next();
        std::string* temp = new std::string[2];
        temp[0] = query.value(0).toString().toStdString();
        temp[1] = query.value(1).toString().toStdString();
        *output = temp;
        return true;
    }
    std::string* temp = new std::string[1];
    temp[0] = "Error this user does not exist";
    *output = temp;
    return false;
}
//UNTESTED BEWARE!
bool database::addFriendReq(std::string username, std::string friendUsername){
    QSqlQuery query;
    std::string init;
    std::string recipient;
    query.exec(("SELECT userID FROM Users WHERE username = '"+username+"'").c_str());
    if(!query.isActive())
        return false;
    query.next();
    init = query.value(0).toString().toStdString();
    query.exec(("SELECT userID FROM Users WHERE username = '"+friendUsername+"'").c_str());
    if(!query.isActive())
        return false;
    query.next();
    recipient = query.value(0).toString().toStdString();
    std::ostringstream oss;
    oss << currentFriendNumber;
    return query.exec(("INSERT INTO Friends VALUES("+oss.str()+",'"+init+"','"+recipient+"'").c_str());
}
//NOT TESTED!!!
bool database::updateContactInfo(std::string username, std::string ipaddress, std::string port){
    QSqlQuery query;
    return query.exec(("UPDATE Users SET ipaddress ='"+ipaddress+"', port ='"+port+"' WHERE Users.username ='"+username+"'").c_str());
}
