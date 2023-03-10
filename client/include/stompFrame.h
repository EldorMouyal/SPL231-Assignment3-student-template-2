#pragma once
//#include <stdlib.h>
#include <string>
#include <vector>
using std::vector;

class stompFrame{

private :
std::string command;
std::vector<std:: string> headers;
std::vector<std:: string> frames;
std::string body;
std::string frame;
int subscriptionID;
int receipt;
void addCommand(std::string header);
void addHeader(std::string key, std::string value);
void setBody(std::string);
void createLoginFrame(std::string port, std::string username, std::string password);
void createJoinFrame(std::string gameName);
void createExitFrame(std:: string gameName, int receipt);
void createReportFrame(std::string report,std::string username);
void createLogoutFrame(int receipt);
std::string buildFrame();


public:
stompFrame(std::vector<std::string> &words, int id, int receipt,std::string username);
std::vector<std::string> getFrames();

};