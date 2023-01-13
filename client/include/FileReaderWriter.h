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
    FileReaderWriter(string team_A,string team_b,string userName);
    ~FileReaderWriter();
    void write(string);
    string read();

private:
    string m_file;
    std::ofstream MyWriteFile;
    bool IsFileEmpty();
    void open();
    void close();
};