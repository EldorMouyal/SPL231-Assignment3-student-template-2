#pragma once
//#include <stdlib.h>
#include <string>
#include <vector>

class stompFrame{

private :
std::string header;
std::vector<std::string> ops;
std::string body;

public:
stompFrame();
void addHeader(std::string header);
void addOp(std::string op);
void addBody(std::string);
bool isFrameComplete();
std::string getFrame();

};
