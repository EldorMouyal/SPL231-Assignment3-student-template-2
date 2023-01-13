#include "../include/FileReaderWriter.h"
using std::cerr;
using std::endl;
using std::ofstream;
using namespace std;

FileReaderWriter::FileReaderWriter(string m_file) : m_file(m_file) {ofstream MyWriteFile(m_file);};

FileReaderWriter::~FileReaderWriter() {};

void FileReaderWriter::write(string line) {
    ofstream file;
    file.open(m_file ,ios::out);
    file << line;
    file.close();
}
void FileReaderWriter::open() {
    ofstream file;
    file.open(m_file);
}
void FileReaderWriter::close() {
    ofstream file;
    file.close();
}