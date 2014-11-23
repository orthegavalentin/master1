#ifndef DECOMPRESSOR_H
#define DECOMPRESSOR_H

#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <boost/dynamic_bitset.hpp>
#include <bitset>
#include <sstream>
#include "utils.h"

using namespace std;

class Decompressor
{
public:
    Decompressor();
    void decompress(string in, string out);

private:
    vector<string> m;
    int k;
    string result;
    string w;
    int ENCODING_LENGTH;

    string pair(string x, char y);
    void writeResult(string out);
    vector<int> decode(string in);
    void initDico();
};

#endif // DECOMPRESSOR_H
