#include "../include/FileReaderWriter.h"
using std::cerr;
using std::endl;
using std::ofstream;
using namespace std;

using std::cerr;
using std::endl;
using std::ofstream;
using namespace std;
using std::string;

//its recommended the string of the fileName will be "TeamA VS Team B UserName_User"
FileReaderWriter::FileReaderWriter(string team_a,string team_b,string userName):MyWriteFile(team_a+" "+team_b+" "+userName),m_file(team_a+" "+team_b+" "+userName) {
if (IsFileEmpty())
{
    open();
    bool isFileEmpty = IsFileEmpty();
    close();
    if (isFileEmpty)
    {
        write(team_a+" VS"+team_b);
    }

}
}

FileReaderWriter::~FileReaderWriter()
{}

void FileReaderWriter::write(string body) {
    ofstream file;
    file.open(m_file, ios::app);
    file << "General stats:\n"+body << "\n\n";
    file.close();
}
string FileReaderWriter::read()
{
    
    string line;
    string output="";
    ifstream myReadfile(m_file);
    if (myReadfile.is_open())
    {
        while (getline(myReadfile, line))
        {
            output+=  line + '\n';
        }
        myReadfile.close();
    }
    return output;

 
}
void FileReaderWriter::open() {
    ofstream file;
    file.open(m_file);
}
void FileReaderWriter::close() {
    ofstream file;
    file.close();
}
bool FileReaderWriter::IsFileEmpty()
{
    return (MyWriteFile.tellp() == 0);
}