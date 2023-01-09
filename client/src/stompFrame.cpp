#include "../include/stompFrame.h"
using namespace std;

stompFrame:: stompFrame(string line, int clientid, int _receipt){
this->clientID = clientid;
this->receipt = _receipt;

int i=0 ;
string command = "";
while(i<line.length()){
command += line[i];
if(command == "login"){
    addCommand("CONNECT");//createLoginFrame
    break;
}
if(command == "join"){
    addCommand("SUBSCRIBE");
    break;
}
if(command == "exit"){
    addCommand("UNSUBSCRIBE");
    break;
}
if(command == "report"){
    addCommand("SEND");
    break;
}
if(command == "logout"){
    addCommand("DISCONNECT");
}
}
}

void stompFrame:: createLoginFrame(string host, string port, string username, string password){
    addCommand("CONNECT");
    addHeader("accept-version","1.2");
    addHeader("host","stomp.cs.bgu.ac.il");
    addHeader(username,password);
}

void stompFrame:: createJoinFrame(string gameName){
    addCommand("SUBSCRIBE");
    addHeader("destination","/"+gameName);
    addHeader("id", ""+ clientID);
    addHeader("receipt", ""+ receipt);
}

void stompFrame:: createExitFrame(string gameName, int receipt){// where do i get the receipt id according to the gameName?
    addCommand("UNSUBSCRIBE");
    addHeader("id", ""+ clientID);
    addHeader("receipt", ""+ receipt);
}
void stompFrame:: createReportFrame(string report){
    addCommand("SEND");// TODO: IMPLEMENT LATER
}
 void stompFrame:: createLogoutFrame(int receipt){
    addCommand("DISCONNECT");
    addHeader("receipt", ""+receipt);
 }

void stompFrame:: addCommand(string _command){  
        this->command = _command;
}

void stompFrame:: addBody(string _body){
    if(_body.length() > 0)
        this->body += _body;
}

void stompFrame:: addHeader(string key, string value){
     string header =  key + ":" + value + "\n";
     headers.push_back(header);
}

void stompFrame:: buildFrame(){
    string out = command + "\n";
    for(int i=0; i<headers.size(); i++){
        out += (headers[i]);
        out += "\n";
    }

    out += "\n";// 

    if(body.length() >0)
        out += (body) + "\n";

    out += "\0";
}

