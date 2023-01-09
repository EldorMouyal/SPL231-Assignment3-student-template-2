#include "../include/stompFrame.h"
using namespace std;

stompFrame:: stompFrame(){
    
}

void stompFrame:: addHeader(string _header){
    if(_header.length() >0)
        this->header = _header;
}

void stompFrame:: addBody(string _body){
    if(_body.length() >0)
        this->body += _body;
}

void stompFrame:: addOp(string op){
    if(op.length() > 0)
        ops.push_back(op);
}

string stompFrame:: getFrame(){
    string out = header + "\n";
    for(int i=0; i<ops.size(); i++){
        out += (ops[i]);
        out += "\n";
    }
    out += "\n";

    out += (body);
}

