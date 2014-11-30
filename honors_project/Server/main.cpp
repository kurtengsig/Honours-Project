#include "monitoringwindow.h"
#include <QApplication>
#include "database.h"
#include <QDebug>
#include "encoder.h"
#include <iostream>
#include "connection.h"
//#include <thread>
#include "controller.h"
int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    //MonitoringWindow w;
    //database d;
    //std::string output;
    //std::cout << d.loginReq("Kurt", "password", &output) << "\n" << output <<"\n";
    Controller c;
    //w.show();
    //std::thread newThread (a.exec);
    //network n;
    //std::string o = "";
    //
    //DATABASE TESTS
    //database d;
    //Connection* c;
    //while(1){
    //    c = new Connection();
    //    delete(c);
    //}
    //qDebug() << "Attempting an invalid user:";
    //d.loginReq("Jeff", "mcclelland", &output);
    //qDebug() << output.c_str();
    //qDebug() << "Attempting a valid user";
    //d.loginReq("Kurt", "password", &o);
    //d.loginReq("Susan", "lee", &o);
    //d.loginReq("James", "pippy", &o);
    //qDebug() << output.c_str();
    //d.logoutReq("Kurt");
    //qDebug() << "Adding a new user";
    //d.registerUserReq("jeff", "mcclelland", &output);
    //qDebug() << output.c_str();
    //d.miscFunction("SELECT * FROM Users INNER JOIN Friends ON Users.userID==Friends.friendID WHERE Users.status == 'Online' AND Friends.userID ==1003");
    //std::string* output;
    /*int size;
    d.friendsListReq("Kurt", &output, &size);
    for(int i=0; i<size; ++i){
        qDebug() << output[i].c_str();
    }*/
    //d.contactInfoReq("Kurt", &output);
    //for(int i=0; i<2; i++)
    //    qDebug() << output[i].c_str();
    //qDebug() << d.validateLogin("Kurt", "passwordd");
    //
    //ENCODING/DECODING TESTS
    //encoder e;
    //std::string* r;
    //std::string s[4] ={"Hi", "my", "name", "is"};
    //std::string str = e.encode(s,4);
    //e.decode(&r, str);
    //
    //NETWORKING TESTS
    //n.create();
    //n.receiveMessage();
    //a.exec();
}
