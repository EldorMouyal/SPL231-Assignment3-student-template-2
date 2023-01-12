#include "../include/FileReaderWriter.h"
using std::cerr;
using std::endl;
using std::ofstream;

FileReaderWriter::FileReaderWriter(string fileName) : file(file) {ofstream MyWriteFile("filename.txt");};

FileReaderWriter::~FileReaderWriter() {};

void FileReaderWriter::write(string line) {
    ofstream file;
    file.open(file,ios::out);
    file << line;
    file.close();
}
void FileReaderWriter::open() {
    ofstream file;
    file.open(path);
}
void FileReaderWriter::close() {
    ofstream file;
    file.close();
}