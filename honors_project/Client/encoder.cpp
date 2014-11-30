#include "encoder.h"

encoder::encoder(){
}
/* Summary: This function works to encode an array of inputs into a single string which is returned
 * Input parameter: input <string*> the array of strings to be encoded
 *                  numberOfInputs<int> the number of elements in the array
 * Output parameter: output<string> string of inputs which have been concattenated together
 * Upon Completion: A string is returned which contains all of the inputs which are seperated using
 *                  a specified delimiter
 */
std::string encoder::encode(std::string* input, int numberOfInputs){
    std::string output;
    for(int i = 0; i< numberOfInputs-1; i++){
        output += input[i] + "~!~";
    }
    output += input[numberOfInputs-1];
    return output;
}
/* Summary: This function works to decode a string and save each value into a position in a new array
 * Input parameter: input <string> the message to be decoded
 * Output parameter: output<string**> the pointer to the array that is to be returned
 * Upon Completion: An array has been allocated dynamically and the output pointer is pointing at it
 */
void encoder::decode(std::string** output, int* size, std::string input){
    std::vector<std::string> v; // used until the string has been completely split and the size is known
    std::string s = input;
    std::string delimiter = "~!~";
    int position = 0;
    std::string piece;

    while((position = s.find(delimiter)) != std::string::npos){
        piece = s.substr(0, position);
        v.push_back(piece);
        s.erase(0, position+delimiter.length());
    }
    v.push_back(s);
    std::string* temp = new std::string[v.size()];
    *size = v.size();
    for(int i =0; i < v.size(); i++)
        temp[i] = v[i];
    *output = temp;
}
