#include "compressor.h"

Compressor::Compressor()
{
    m = new unordered_map<string, long>;
    oufman = new map<long, int>;
    chars = new vector<int>;

    initDico();
    w = "";
    result = "";
    index = 256;
    charCpt = 0;
    nbBar = 0;
}

void Compressor::compress(string in, string out)
{
    size = Utils::getFileSize(in);
    //cout << "size : " << size << endl;
    char c;
    string temp = "";
    ifstream infile;
    infile.open(in, ios::binary | ios::in);
    while(!infile.eof()) {
        infile.read(&c, 1);
        charCpt++;

        float f = (float)charCpt / (float)size;
        if( f * 100 > nbBar) {
            nbBar++;
            Utils::drawProgressBar("compressing : ", nbBar);
        }

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
            long n = m->at(w);
            if(huffman) {
                chars->push_back(n);
                computeOufman(n);
                //cout << n << endl;
            } else {
                result += std::bitset<ENCODING_LENGTH>(n).to_string();
            }
            w = pair("", c);
        }
    }
    if(huffman) {
        computeOufman(m->at(w));
        chars->push_back(m->at(w));
        Huffman *h = new Huffman(oufman);
        result = h->convertToString(chars);
    } else {
        result += std::bitset<ENCODING_LENGTH>(m->at(w)).to_string();
        string encodingLength = std::bitset<8>(ENCODING_LENGTH).to_string();
        result = encodingLength + result;
    }
    writeResult(out);
}

void Compressor::writeResult(string out)
{
    ofstream myFile;
    myFile.open(out, ios::out | ios::binary);
    int n = result.size() % 8;
    char c[1];

    for (int var = 0; var < n; ++var) {
        result += "0";
    }
    nbBar = 0;
    for (long var = 0; var < result.size() / 8; ++var) {
        float f = (float)var / ((float)result.size() / 8);
        if( f * 100 > nbBar) {
            nbBar++;
            Utils::drawProgressBar("writing to file : ", nbBar);
        }
        int temp = std::bitset<8>(result.substr(var * 8, 8)).to_ulong();
        c[0] = temp;
        myFile.write(c, 1);
    }
    myFile.close();
}

void Compressor::computeOufman(long s)
{
    if(oufman->find(s) != oufman->end()) {
        oufman->at(s)++;
    } else {
        oufman->insert(std::pair<long, int>(s, 1));
    }
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




