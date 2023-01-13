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
    
