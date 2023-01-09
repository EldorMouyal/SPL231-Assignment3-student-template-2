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
void addCommand(std::string header);
void addHeader(std::string key, std::string value);
void addBody(std::string);
bool isFrameComplete();
std::string getFrame();

};
