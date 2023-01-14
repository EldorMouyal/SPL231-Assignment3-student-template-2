#include <stdlib.h>
#include "../include/ConnectionHandler.h"
#include <thread>
#include <vector>
#include "../include/stompFrame.h"
using namespace std;

int receipt = 0;
int subscriptionID = 0;
string connectedUser;
ConnectionHandler *cHandler;
bool userConnected = false;
bool isPullThreadStarted = false;

static vector<string> split(const string &str, char delimiter)
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

string getLine()
{
    const short bufsize = 1024;
    char buf[bufsize];
    std::cin.getline(buf, bufsize);
    std::string line(buf);
    return line;
}

static vector<string> getWords()
{
    std::string line = getLine();
    vector<string> words = split(line, ' ');
    return words;
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

bool sendLineFrame(string line)
{
    vector<string> words = split(line, ' ');
    return sendFrame(words);
}

bool getLineAndSendFrame()
{
    std::string line = getLine();
    return sendLineFrame(line);
}

void handleLoginCommand(vector<string> words)
{
    if (words.size() >= 2)
    {
        string portstr = words[1].substr(words[1].find(':') + 1, words[1].length());
        vector<string> hostPort = split(words[1], ':');
        connectedUser = words[2];
        short port = stoi(hostPort[1]);
        cHandler = new ConnectionHandler(hostPort[0], port);

        if (cHandler->connect())
        {
            // Sending login information...
            sendFrame(words);

            // Getting login response.
            string loginResponse;
            if (cHandler->getLine(loginResponse))
            {
                cout << loginResponse << endl;
                // Decode STOMP frame and check for login confirmation.

                // When login successfull...
                userConnected = true;
            }
            else
            {
                cout << "Could not perform the login operation" << endl;
            }
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

void pullThreadMethod(ConnectionHandler &handler)
{
    while (userConnected)
    {
        string line;
        if (cHandler->getLine(line))
        {
            //if line is subscription confirmation or topic feed.
        }
    }
}

void handleSubscribeCommand(vector<string> words)
{
    if (sendFrame(words))
    {
        if (!isPullThreadStarted)
        {
            isPullThreadStarted = true;
            std::thread pullThread(pullThreadMethod, cHandler);
        }
    }
    else
    {
        // Handle send error
    }
}

void handleLogoutCommand()
{
    if (sendLineFrame("logout"))
    {
        userConnected = false;
        isPullThreadStarted = false;
        cHandler->close();
    }
    else
    {
        //Handle logout error.
    }
}

int main(int argc, char *argv[])
{
    cout << "Client Started" << endl;
    string host;
    short port;

    while (1)
    {
        vector<string> words = getWords();
        string command = words[0];

        if (command == "login" && userConnected)
        {
            cout << "Already logged in" << endl;
        }
        else if (command != "login" && !userConnected)
        {
            cout << "Must login first" << endl;
        }
        else if (command == "login")
        {
            handleLoginCommand(words);
        }
        else if (command == "subscribe")
        {
            handleSubscribeCommand(words);
        }
        else if (command == "logout")
        {
            handleLogoutCommand();
        }
        else if (command == "exit")
        {
            handleLogoutCommand();
            return 0;
        }
        else
        {
            cout << "Invalid command" << endl;
        }
    }

    return 0;
}
