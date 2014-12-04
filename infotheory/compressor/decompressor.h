#ifndef DECOMPRESSOR_H
#define DECOMPRESSOR_H

#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
#include <sstream>
#include <math.h>

#include "huffman.h"
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
    vector<int> decompressRegular(ifstream *infile, int ENCODING_LENGTH);
    vector<int> parseHuffman(ifstream *infile);
    vector<int> decompressHuffman(ifstream* infile, Huffman* h, string temp);
    void initDico();
    long size;
    int nbBar;
};

#endif // DECOMPRESSOR_H
