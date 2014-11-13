#ifndef ENCODER_H
#define ENCODER_H
#include <string>
#include <QDebug>
#include <vector>

class encoder
{
public:
    encoder();
    std::string encode(std::string* input, int numberOfInputs);
    void decode(std::string** output, std::string input);
};

#endif // ENCODER_H
