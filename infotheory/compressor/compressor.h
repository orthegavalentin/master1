#ifndef COMPRESSOR_H
#define COMPRESSOR_H

#include <map>
#include <string>
#include <bitset>
#include <fstream>
#include <iostream>
#include <math.h>
#include <sstream>
#include <huffman.h>

#include "utils.h"

using namespace std;

class Compressor
{
public:
    Compressor();
    static const int ENCODING_LENGTH = 12;
    void compress(string in, string out);

private:
    map<string, long>* m;
    map<long, int>* oufman;
    long index;
    string result;
    string w;
    long charCpt, size;
    int nbBar;

    void initDico();
    string pair(string x, char y);
    void writeResult(string out);
    void computeOufman(long s);
};

#endif // COMPRESSOR_H
