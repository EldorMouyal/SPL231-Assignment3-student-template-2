#include <stdlib.h>
#include "../include/ConnectionHandler.h"
#include <thread>
#include <vector>
#include "../include/stompFrame.h"
using namespace std;

static std::vector<std::string> split(const std::string &str, char delimiter)
{
    std::vector<std::string> result;
    std::string current;
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

int receipt = 0;
int subscriptionID = 0;
string connectedUser;
ConnectionHandler *cHandler;

int main(int argc, char *argv[])
{
    cout << "Client Started" << endl;
    bool userConnected = false;
    string host;
    short port;

    while (1)
    {
        vector<string> words = getWords();
        string command = words[0];

        if (command == "login")
        {
            if (words.size() >= 2)
            {
                string portstr = words[1].substr(words[1].find(':') + 1, words[1].length());
                vector<string> hostPort = split(words[1], ':');
                connectedUser = words[2];
                port = stoi(hostPort[1]);
                cHandler = new ConnectionHandler(hostPort[0], port);
                if (cHandler->connect())
                {
                    sendFrame(words);
                    userConnected = true;
                }
                else
                {
                    cout << "Connection error occurred" << endl;
                }
            }
            else
            {
                cout << "invalid login input" << endl;    
            }
        }
        else
        {
            cout << "to perform any action please log in first" << endl;
        }
    }

    // std:: thread keyboardThread (keyboardInput , cHandler);

    return 0;
}

vector<string> getWords()
{
    std::string line = getLine();
    vector<string> words = split(line, ' ');
    return words;
}

string getLine()
{
    const short bufsize = 1024;
    char buf[bufsize];
    std::cin.getline(buf, bufsize);
    std::string line(buf);
    return line;
}

bool getLineAndSendFrame()
{
    std::string line = getLine();
    return sendFrame(line);
}

bool sendFrame(string line)
{
    vector<string> words = split(line, ' ');
    return sendFrame(words);
}

bool sendFrame(vector<string> words)
{
    cout << "creating frame" << endl;
    stompFrame frame = stompFrame(words, subscriptionID, receipt);
    vector<string> frames = frame.getFrames();
    cout << frames[0] << endl; // up to here;
    for (int i = 0; i < frames.size(); i++)
    {
        int len = frames[i].length();
        if (!cHandler->sendLine(frames[i]))
        {
            std::cout << "Disconnected. Exiting...\n"
                      << std::endl;
            return false;
        }
        // connectionHandler.sendLine(line) appends '\n' to the message. Therefor we send len+1 bytes.
        std::cout << "Sent " << len + 1 << " bytes to server" << std::endl;
    }

    return true;
}

void keyboardInput(ConnectionHandler &handler)
{
    while (1)
    {
        const short bufsize = 1024;
        char buf[bufsize];
        std::cin.getline(buf, bufsize);
        std::string line(buf);

        vector<string> frames = split(line, ' ');
        for (int i = 0; i < frames.size(); i++)
        {
            int len = frames[i].length();
            if (!handler.sendLine(frames[i]))
            {
                std::cout << "Disconnected. Exiting...\n"
                          << std::endl;
                break;
            }
            // connectionHandler.sendLine(line) appends '\n' to the message. Therefor we send len+1 bytes.
            std::cout << "Sent " << len + 1 << " bytes to server" << std::endl;
        }
    }
}

void connectionInput(ConnectionHandler &handler)
{
}
