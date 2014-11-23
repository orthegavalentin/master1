#include "compressor.h"

Compressor::Compressor()
{
    m = new map<string, long>;
    initDico();
    w = "";
    result = "";
    index = 256;
}

void Compressor::compress(string in, string out)
{
    char c;
    string temp = "";
    ifstream infile;
    infile.open(in, ios::binary | ios::in);
    while(!infile.eof()) {
        infile.read(&c, 1);

        if(index >= pow(2, ENCODING_LENGTH)) {
            m->clear();
            initDico();
            index = 256;
        }
        temp = pair(w, c);
        if(m->find(temp) != m->end()) {
            w = temp;
        } else {
            m->insert(std::pair<string, long>(temp, (long)index));
            index++;
            result += std::bitset<ENCODING_LENGTH>(m->at(w)).to_string();
            w = pair("", c);
        }
    }
    result += std::bitset<ENCODING_LENGTH>(m->at(w)).to_string();
    string encodingLength = std::bitset<8>(ENCODING_LENGTH).to_string();
    result = encodingLength + result;
    writeResult(out);
}

void Compressor::writeResult(string out)
{
    ofstream myFile;
    myFile.open(out, ios::out | ios::binary);
    int n = result.size() % 8;
    char c[1];

    for (long var = 0; var < result.size() / 8 - n; ++var) {
        int temp = std::bitset<8>(result.substr(var * 8, 8)).to_ulong() - 127;
        c[0] = temp;
        myFile.write(c, 1);
    }
    cout << "size : " << result.size() / 8 << endl;
    myFile.close();
}

void Compressor::initDico()
{
    for (int var = 0; var < 256; ++var) {
        m->insert(std::pair<string, long>(pair("", var), var));
    }
}

string Compressor::pair(string x, char y)
{
    stringstream ss;
    string s;
    ss << y;
    return x + y;
}


