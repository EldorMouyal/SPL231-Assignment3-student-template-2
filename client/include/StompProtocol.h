#pragma once

#include "../include/ConnectionHandler.h"
#include "../include/stompFrame.h"
#include <string>
using std::string;

// TODO: implement the STOMP protocol
class StompProtocol
{
private:

public:
string reportProcess(string report);
string getName(string report);
};
