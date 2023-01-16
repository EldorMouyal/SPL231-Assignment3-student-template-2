#include "../include/StompProtocol.h"

using std::string;

StompProtocol::StompProtocol(ConnectionHandler &connectionHandler) : cHandler(connectionHandler)
{

}
void StompProtocol::Process(string msg)
{
    if(isReportMsg(msg))
    {
        string body = getBodyOfReport(msg);
        string name = getName(msg);
        vector<string> teams = getTeamsNames(msg);
        string team_a = teams[0];
        string team_b = teams[1];
        FileReaderWriter doc(team_a,team_b,name);
        doc.write(body);
    }

    else if(isConnectedMsg(msg))
    {
    }

    else if(isErrorMsg(msg))
    {
        cHandler.close();
    }

    else if(isReceiptMsg(msg))
    {
    }

    else if(isDisconnectedMsg(msg))
    {
        cHandler.close();
    }

}
string StompProtocol::getBodyOfReport(string report)
{
    string body= report;
    int numOfEnters =4;
    string delimiter = "\n";
    int position = 0;    
    while(numOfEnters>0){        
        position = body.find(delimiter);
        numOfEnters--;
    }
    body.erase(0, position +1);
    body=body.substr(0,body.size()-1);//deletes the last null carectar in the substring
    return body;
}
bool StompProtocol::isConnectedMsg(string msg)
{
 vector<string> words = split(msg,'\n');
    if(words.size()>0&&words[1] == "CONNECTED")
        return true;
    return false;
}
bool StompProtocol::isReportMsg(string msg)
{
    vector<string> words = split(msg,'\n');
    if(words.size()>0&&words[0] == "SEND")
        return true;
    return false;
}
bool StompProtocol::isErrorMsg(string msg)
{
 vector<string> words = split(msg,'\n');
    if(words.size()>0&&words[1] == "ERROR")
        return true;
    return false;
}
bool StompProtocol::isReceiptMsg(string msg)
{
    vector<string> words = split(msg,'\n');
    if(words.size()>0&&words[1] == "RECEIPT")
        return true;
    return false;
}

int StompProtocol::getReceiptId(string msg)//suitable for disconnected an reciept fram
{
    vector<string> words = split(msg,'\n');
    string id = words[2];
    id.erase(0, id.find(":")+1);
    return stoi(id);
}

bool StompProtocol::isDisconnectedMsg(string msg)
{
    vector<string> words = split(msg,'\n');
    if(words.size()>0&&words[0] == "DISCONNECTED")
        return true;
    return false;
}


string StompProtocol::getName(string report)
{
    string output= report;
    int numOfEnters =3;
    string delimiter = "\n";
    int position = 0;    
    while(numOfEnters>0){        
        position = output.find(delimiter);
        numOfEnters--;
    }
    output.erase(0, position +1);
    numOfEnters =1;
    while(numOfEnters>0){        
        position = output.find(delimiter);
        numOfEnters--;
    }
    output.erase(position, output.size()+1-position);//name:XXXX is output value by now
    output.erase(0, output.find(":")+1);//XXXX is output value by now
    return output;
}
vector<string> StompProtocol::getTeamsNames(string msg)//need to change
{
  string team_a="";
  string team_b="";
  vector<string> output;

    vector<string> words = split(msg,'\n');
    for(int i=0;i<words.size();i++){
        if(words[i].find("destination") == 0){
            vector<string> destination = split(words[i],':');
            vector<string> teams   = split(destination[1],'_');
            output.push_back(teams[0]);
            output.push_back(teams[1]);
            break;
    }
    }
    return output;
}

 vector<string> split(const string &str, char delimiter)
{
    vector<string> result;
    string current;
    for (const char &c : str)
    {
        if (c == delimiter)
        {
            result.push_back(current);
            current.clear();
        }
        else
        {
            current += c;
        }
    }
    result.push_back(current);
    return result;
}
    
