#pragma once

#include "../include/ConnectionHandler.h"
#include "../include/stompFrame.h"
#include "../include/FileReaderWriter.h"
#include <string>
using namespace std;

// TODO: implement the STOMP protocol
class StompProtocol
{
private:
ConnectionHandler &cHandler;
map<int, string> receiptIds;
int logoutReceipt;


public:
StompProtocol(ConnectionHandler &connectionHandler);
vector<string> Split(const string &str, char delimiter);//splits the string by the delimiter
bool Process(string report);//
string getBodyOfReport(string report);//gets the body of the report
string getName(string report);//gets the name of the user from a report
bool isConnectedMsg(string msg);//returns true for connected frame
bool isReportMsg(string msg);//returns true if the message is a report frame
bool isErrorMsg(string msg);//returns true for error frame
bool isReceiptMsg(string msg);//returns true for reciept frame
int getReceiptId(string msg);//suitable for disconnected an reciept frames
vector<string> getTeamsNames(string msg);//returns the teams names from the server
bool isDisconnectedMsg(string msg);//eturns true for disconnected frame
bool insertReceiptAndResponse(int id, string response);//inserts the receipt id to the maps the respons acoordingly
string getResponse(int id);//returns the response of the receipt id
void setLogoutReceipt(int id);//sets the logout receipt id
};
