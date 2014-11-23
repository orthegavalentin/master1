#ifndef COMPRESSOR_H
#define COMPRESSOR_H

#include <map>
#include <string>
#include <bitset>
#include <fstream>
#include <iostream>
#include <math.h>
#include <sstream>
#include <boost/lexical_cast.hpp>

using namespace std;

class Compressor
{
public:
    Compressor();
    static const int ENCODING_LENGTH = 12;
    void compress(string in, string out);

private:
    map<string, long>* m;
    long index;
    string result;
    string w;
    void writeResult(string out);
    void initDico();
    string pair(string x, char y);
};

#endif // COMPRESSOR_H
