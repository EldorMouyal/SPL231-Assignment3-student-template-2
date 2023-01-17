#include "../include/stompFrame.h"
#include "../include/event.h"
using namespace std;

stompFrame::stompFrame(vector<string> &words, int _subscriptionID, int _receipt,string username) : headers(), frames(), body(), frame(), subscriptionID(_subscriptionID), receipt(_receipt)
{
    string command = words[0];

    if (command == string("login"))
    {
        string port = words[1].substr(words[1].find(':') + 1, words[1].length());
        createLoginFrame(port, words[2], words[3]);
    }
    if (command == "join")
    {
        createJoinFrame(words[1]);
    }
    if (command == "exit")
    {
        createExitFrame(words[1], receipt); // TODO: implement this properley later
    }
    if (command == "report")
    {
        createReportFrame(words[1],username); // TODO: implement this later
    }
    if (command == "logout")
    {
        createLogoutFrame(receipt); // where do I get this receipt from?
    }
}

void stompFrame::createLoginFrame(string port, string username, string password)
{

    addCommand("CONNECT");
    addHeader("accept-version", "1.2");
    addHeader("host", "stomp.cs.bgu.ac.il");
    addHeader("login", username);
    addHeader("passcode", password);

    frames.push_back(buildFrame());
}

void stompFrame::createJoinFrame(string gameName)
{
    addCommand("SUBSCRIBE");
    addHeader("destination", "/" + gameName);
    addHeader("id", "" + to_string(subscriptionID));
    addHeader("receipt", "" + to_string(receipt));
    frames.push_back(buildFrame());
}

void stompFrame::createExitFrame(string gameName, int receipt)
{ // where do i get the receipt id according to the gameName?
    addCommand("UNSUBSCRIBE");
    addHeader("id", "" + to_string(subscriptionID));
    addHeader("receipt", "" + to_string(receipt));
    frames.push_back(buildFrame());
}

void stompFrame::createReportFrame(string file,string username)
{
    names_and_events nae = parseEventsFile(file);
    addCommand("SEND");
    addHeader("destination", '/' + nae.team_a_name + '_' + nae.team_b_name);
    for (int i = 0; i < nae.events.size(); i++)
    {
        string body = "user: "+username+ '\n';
        body += "team a: " + nae.team_a_name + '\n';
        body += "team b: " + nae.team_b_name + '\n';
        body += "event name: " + nae.events[i].get_name() + '\n';
        body += "time: " + std::to_string(nae.events[i].get_time()) + "\ngeneral game updates: \n";
        std::map<string,string> gameUpdates = nae.events[i].get_game_updates();
        for (pair<string, string> p: gameUpdates)
        {
<<<<<<< HEAD
            body += "   " + p.first + ':' + p.second + '\n';
=======
            body += "\t" + p.first + ":" + p.second + "\n";
>>>>>>> omerFixServerBranch
        }
        body += "team a updates:\n";
        std::map<string,string> AUpdates = nae.events[i].get_team_a_updates();
        for (pair<string, string> p : AUpdates)
        {
<<<<<<< HEAD
            body += "   " + p.first + ':' + p.second + '\n';
=======
            body += "\t" + p.first + ":" + p.second + "\n";
>>>>>>> omerFixServerBranch
        }
        body += "team b updates:\n";
        map<string, string> BUptates = nae.events[i].get_team_b_updates();
        for (pair<string, string> p : BUptates)
        {
<<<<<<< HEAD
            body += "   " + p.first + ':' + p.second + '\n';
=======
            body += "\t" + p.first + ":" + p.second + "\n";
>>>>>>> omerFixServerBranch
        }
        body += "description:\n" + nae.events[i].get_discription();
        setBody(body);
        frames.push_back(buildFrame());
    }
}
void stompFrame::createLogoutFrame(int receipt)
{ // where do I get this recipt from?
    addCommand("DISCONNECT");
    addHeader("receipt", "" + to_string(receipt));
    frames.push_back(buildFrame());
}

void stompFrame::addCommand(string _command)
{
    this->command = _command;
}

void stompFrame::setBody(string _body)
{
    if (_body.length() > 0)
        this->body = _body;
}

void stompFrame::addHeader(string key, string value)
{
    string header = key + ":" + value + "\n";
    headers.push_back(header);
}

vector<string> stompFrame::getFrames()
{
    return frames;
}

string stompFrame::buildFrame()
{
    string out = command + "\n";
    for (int i = 0; i < headers.size(); i++)
    {
        out += (headers[i]);
    }

    out += "\n"; //

    if (body.length() > 0)
        out += (body) + "\n";

    out += "\0";
    return out;
}
