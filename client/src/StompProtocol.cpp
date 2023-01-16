#include "../include/StompProtocol.h"

using std::string;

StompProtocol::StompProtocol(ConnectionHandler &connectionHandler) : cHandler(connectionHandler)
{
    map<int, string> receiptIds();
    logoutReceipt = -1;
}

vector<string> StompProtocol::Split(const string &str, char delimiter)
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
//================================================================================================
bool StompProtocol::Process(string msg)
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

    else if(isErrorMsg(msg))
    {
        cHandler.close();
    }

    else if(isReceiptMsg(msg))
    {
        string response= getResponse(getReceiptId(msg));
        int id = getReceiptId(msg);
        cout<<response<<endl;
        if(id == logoutReceipt)
        {
            return false;
        }
        
    }

    else if(isDisconnectedMsg(msg))
    {
        
    }
    return true;

}
//================================================================================================

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
 vector<string> words = Split(msg,'\n');
    if(words.size()>0&&words[0] == "CONNECTED")
        return true;
    return false;
}
bool StompProtocol::isReportMsg(string msg)
{
    vector<string> words = Split(msg,'\n');
    if(words.size()>0&&words[0] == "SEND")
        return true;
    return false;
}
bool StompProtocol::isErrorMsg(string msg)
{
 vector<string> words = Split(msg,'\n');
    if(words.size()>0&&words[0] == "ERROR")
        return true;
    return false;
}
bool StompProtocol::isReceiptMsg(string msg)
{
    vector<string> words = Split(msg,'\n');
    if(words.size()>0&&words[0] == "RECEIPT")
        return true;
    return false;
}

int StompProtocol::getReceiptId(string msg)//suitable for disconnected an reciept fram
{
    vector<string> words = Split(msg,'\n');
    string id = words[1];
    id.erase(0, id.find(":")+1);
    return stoi(id);
}

bool StompProtocol::isDisconnectedMsg(string msg)
{
    vector<string> words = Split(msg,'\n');
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

    vector<string> words = Split(msg,'\n');
    for(int i=0;i<words.size();i++){
        if(words[i].find("destination") == 0){
            vector<string> destination = Split(words[i],':');
            vector<string> teams   = Split(destination[1],'_');
            output.push_back(teams[0]);
            output.push_back(teams[1]);
            break;
    }
    }
    return output;
}

bool StompProtocol::insertReceiptAndResponse(int receiptId, string response)
{
    
    if(receiptIds.find(receiptId) == receiptIds.end())
    {
        receiptIds.insert({receiptId,response});
        return true;
    }
    return false;
}

string StompProtocol::getResponse(int receiptId)
{
    if(receiptIds.find(receiptId) != receiptIds.end())
    {
        string response = receiptIds[receiptId];
        receiptIds.erase(receiptId);
        return response;
    }
    return "not a valid receipt id";
}
 
void StompProtocol::setLogoutReceipt(int id)
{
    logoutReceipt = id;
}
    
