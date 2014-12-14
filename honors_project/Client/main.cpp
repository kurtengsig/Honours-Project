#include "controller.h"
#include "peerconnectionlistener.h"
#include "peerconnectionsender.h"
#include <thread>
#include <iostream>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //PeerConnectionSender* q;
    //q->sendMessage("localhost", "8001", "", "HELLO WORLD BITCHEZ");
    controller c;
    return a.exec();
}
