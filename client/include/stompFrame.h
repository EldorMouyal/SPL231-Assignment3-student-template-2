#pragma once
//#include <stdlib.h>
#include <string>
#include <vector>

class stompFrame{

private :
std::string command;
std::vector<std::string> headers;
std:: vector<std:: string> frames;
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
void createReportFrame(string report, string userName);
void createLogoutFrame(int receipt);
std::string buildFrame();


public:
stompFrame(vector<string> words, int id, int receipt);
vector<string> getFrames();

};