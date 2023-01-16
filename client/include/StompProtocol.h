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
bool isConnectedMsg(string msg);//returns true for connected frame
bool isErrorMsg(string msg);//returns true for error frame
bool isReceiptMsg(string msg);//returns true for reciept frame
int getReceiptId(string msg);//suitable for disconnected an reciept frames
bool isDisconnectedMsg(string msg);//eturns true for disconnected frame
};
