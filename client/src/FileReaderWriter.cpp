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

FileReaderWriter::FileReaderWriter(string m_fileName):MyWriteFile(m_fileName),m_file(m_fileName) {}

FileReaderWriter::~FileReaderWriter() {}

void FileReaderWriter::write(string line) {
    ofstream file;
    file.open(m_file, ios::app);
    file << line << "\n\n\n";
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