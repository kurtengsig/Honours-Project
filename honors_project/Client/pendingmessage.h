#ifndef MESSAGE_H
#define MESSAGE_H
#include <string>
class PendingMessage{
private:
    std::string message;
    std::string origin;
public:
    PendingMessage(std::string o, std::string m);
    std::string getOrigin();
    std::string getMessage();
};

#endif // MESSAGE_H
