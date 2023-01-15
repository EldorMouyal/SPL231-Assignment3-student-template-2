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
bool StompProtocol::IsConnectedMsg(string msg)
{
 vector<string> words = split(msg,'\n');
    if(msg == "CONNECTED")
        return true;
    return false;
}

string StompProtocol::getName(string report)
{
    int numOfEnters =3;
    string delimiter = "\n";
    int position = 0;    
    while(numOfEnters>0){        
        position = report.find(delimiter);
        numOfEnters--;
    }
    report.erase(0, position +1);
    numOfEnters =1;
    while(numOfEnters>0){        
        position = report.find(delimiter);
        numOfEnters--;
    }
    report.erase(position, report.size()+1-position);
    return report;
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
    
