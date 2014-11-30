#ifndef REQUESTHANDLER_H
#define REQUESTHANDLER_H
#include "encoder.h"
#include "database.h"
#include <iostream>
class RequestHandler
{
public:
    RequestHandler();
    std::string handle(std::string input, database* d);

private:
    encoder* e;
    std::string* values;
    int size;
};

#endif // REQUESTHANDLER_H
