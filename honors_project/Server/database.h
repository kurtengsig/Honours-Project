#ifndef DATABASE_H
#define DATABASE_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <exception>
#include <string>
#include <sstream>
#include <iostream>
class database
{
public:
    database();
    //MUST BE RETURNED TO BEING PRIVATE
    bool loginReq(std::string username, std::string password, std::string ip, std::string port, std::string** output, int* num);
    bool logoutReq(std::string username);
    bool registerUserReq(std::string username, std::string password, std::string* output); // no return required
    bool friendsListReq(std::string username, std::string** output, int* n); // array return required
    bool contactInfoReq(std::string username, std::string** output, int *n); // array return required
    bool addFriendReq(std::string username, std::string friendUsername); // no return string required
private:
    QSqlDatabase db;

    int currentUserNumber;
    int currentFriendNumber;
};

#endif // DATABASE_H
