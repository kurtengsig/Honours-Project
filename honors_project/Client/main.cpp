#include "controller.h"
#include "peerconnectionlistener.h"
#include "peerconnectionsender.h"
#include <thread>
#include <iostream>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    controller c;

    return a.exec();
}
