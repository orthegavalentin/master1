#ifndef COMPRESSOR_H
#define COMPRESSOR_H

#include <map>
#include <string>
#include <bitset>
#include <fstream>
#include <iostream>
#include <math.h>
#include <sstream>
#include <utils.h>

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
    long charCpt, size;
    int nbBar;
};

#endif // COMPRESSOR_H
