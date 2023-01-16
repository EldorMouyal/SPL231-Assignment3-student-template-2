#include "../include/StompProtocol.h"

using std::string;


string StompProtocol::reportProcess(string report)
{
    int numOfEnters =4;
    string delimiter = "\n";
    int position = 0;    
    while(numOfEnters>0){        
        position = report.find(delimiter);
        numOfEnters--;
    }
    report.erase(0, position +1);
    return report;
}
bool StompProtocol::isConnectedMsg(string msg)
{
 vector<string> words = split(msg,'\n');
    if(words.size()>0&&words[1] == "CONNECTED")
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
    
