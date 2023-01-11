#include <stdlib.h>
#include "../include/ConnectionHandler.h"
#include <thread>
#include <vector>
#include "../include/stompFrame.h"
using namespace std;


int receipt = 0;
int subscriptionID = 0;
string connectedUser;
int main(int argc, char *argv[]) {
	bool userConnected = false;
    string host;
    short port;
    vector<string> words;
    const short bufsize = 1024;
    char buf[bufsize];
    ConnectionHandler* cHandler;
    while (1) {
        while(!userConnected){
        std::cin.getline(buf, bufsize);
		std::string line(buf);
        vector<string> words = processLine(line);
        if(words[0] != "login"){
            cout <<"to perform any action please log in first" << endl;
        }
        else{
            string portstr = words[1].substr(words[1].find(':')+1,words[1].length());
                port = stoi(portstr);
                ConnectionHandler c("bgu.spl.ac.il",port);
                cHandler = new ConnectionHandler ("bgu.spl.ac.il",port);
        }
        }
        
        if(words[0] == "report")
        words.push_back(connectedUser);
        stompFrame frame = stompFrame(words, subscriptionID, receipt);
        vector<string> frames = frame.getFrames();
        for(int i=0; i<frames.size(); i++){
            int len = frames[i].length();
            //bool trySend = cHandler->sendLine(frames[i]);
            if (!cHandler->sendLine(frames[i])) {
                std::cout << "Disconnected. Exiting...\n" << std::endl;
                break;
            }
            // connectionHandler.sendLine(line) appends '\n' to the message. Therefor we send len+1 bytes.
            std::cout << "Sent " << len+1 << " bytes to server" << std::endl;
        }
	}
    std::string host = "stomp.cs.bgu.ac.il";
    short port = atoi("1.2");//not related
    ConnectionHandler connectionHandler(host, port);
    if (!connectionHandler.connect()) {
        std::cerr << "Cannot connect to " << host << ":" << port << std::endl;
        return 1;
    }

	std:: thread keyboardThread (keyboardInput , connectionHandler);

	while(1){
		// We can use one of three options to read data from the server:
        // 1. Read a fixed number of characters
        // 2. Read a line (up to the newline character using the getline() buffered reader
        // 3. Read up to the null character
        std::string answer;
        // Get back an answer: by using the expected number of bytes (len bytes + newline delimiter)
        // We could also use: connectionHandler.getline(answer) and then get the answer without the newline char at the end
        if (!connectionHandler.getLine(answer)) {
            std::cout << "Disconnected. Exiting...\n" << std::endl;
            break;
        }
        
		int len = answer.length();
		// A C string must end with a 0 char delimiter.  When we filled the answer buffer from the socket
		// we filled up to the \n char - we must make sure now that a 0 char is also present. So we truncate last character.
        answer.resize(len-1);
        std::cout << "Reply: " << answer << " " << len << " bytes " << std::endl << std::endl;
        if (answer == "\0") {
            std::cout << "Exiting...\n" << std::endl;
            break;
        }
	}
	return 0;
}

void keyboardInput(ConnectionHandler &handler){
	while (1) {
        const short bufsize = 1024;
        char buf[bufsize];
        std::cin.getline(buf, bufsize);
		std::string line(buf);

        //stompFrame frame = stompFrame(processLine(line), subscriptionID, receipt);
        //string serverFrame = frame.getFrame();
        //ine = frame.getFrame();
        vector<string> frames = processLine(line);
        for(int i=0; i<frames.size(); i++){
            int len = frames[i].length();
            if (!handler.sendLine(frames[i])) {
                std::cout << "Disconnected. Exiting...\n" << std::endl;
                break;
            }
            // connectionHandler.sendLine(line) appends '\n' to the message. Therefor we send len+1 bytes.
            std::cout << "Sent " << len+1 << " bytes to server" << std::endl;
        }
	}
}


vector<string> processLine(string input){    
    vector<string> words;
    string word;
    string delimiter = " ";
    int position = 0;    
    while(position = input.find(delimiter) != string::npos){
        words.push_back(input.substr(0, position-1));
        input.erase(0, position +1);        
    }
    // if(words[0] == "report")
    //     words.push_back(connectedUser);
    // stompFrame frame = stompFrame(words, subscriptionID, receipt);
    // return frame.getFrames();
    return words;
}

 
