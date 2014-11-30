#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "monitoringwindow.h"
#include <QApplication>
#include "database.h"
#include <QDebug>
#include "encoder.h"
#include <iostream>
#include "connection.h"
#include "requesthandler.h"

class Controller
{
public:
    Controller();

private:
    database*       d;
    encoder*        e;
    Connection*     c;
    RequestHandler* h;
};

#endif // CONTROLLER_H
