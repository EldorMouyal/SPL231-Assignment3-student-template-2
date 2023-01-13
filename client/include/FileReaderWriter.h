#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <fstream>


using std::string;
class FileReaderWriter
{
public:
    FileReaderWriter(string);
    ~FileReaderWriter();
    void write(string);
    string read();

private:
    string m_file;
    std::ofstream MyWriteFile;
    void open();
    void close();
};