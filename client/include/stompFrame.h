#pragma once
//#include <stdlib.h>
#include <string>
#include <vector>

class stompFrame{

private :
std::string command;
std::vector<std::string> headers;
std::string body;
std::string frame;
int clientID;
int receipt;
void buildFrame();
void addCommand(std::string header);
void addHeader(std::string key, std::string value);
void addBody(std::string);
void createLoginFrame(std::string host, std::string port, std::string username, std::string password);
void createJoinFrame(std::string gameName);
void createExitFrame(std:: string gameName, int receipt);
void createReportFrame(string report);
void createLogoutFrame(int receipt);


public:
stompFrame(string line, int id, int receipt);
std::string getFrame();
void addBody(std::string);

};
