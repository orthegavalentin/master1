#include "decompressor.h"

Decompressor::Decompressor()
{
    result = "";
    initDico();
    nbBar = 0;
}

void Decompressor::decompress(string in, string out)
{
    size = Utils::getFileSize(in);
    ofstream myFile;
    myFile.open(out, ios::out | ios::binary);
    vector<int> chars = decode(in);
    //cout << chars.size() << endl;
    w = (char)chars[0];
    size = chars.size();
    myFile << w;
    string entry;
    nbBar = 0;
    for (long var = 1; var < chars.size() - 1; ++var) {

        float f = (float)var / (float)size;
        if(f * 10 > nbBar) {
            nbBar++;
            Utils::drawProgressBar("decompressing : ", nbBar);
        }

        if(m.size() >= pow(2, ENCODING_LENGTH)) {
            m.clear();
            initDico();
        }
        k = chars[var];
        if(k < m.size()) {
            entry = m.at(k);
            myFile << entry;
            m.push_back(w + entry.at(0));
            w = entry;
        } else {
            entry = w + w.at(0);
            myFile << entry;

            m.push_back(entry);
            w = entry;
        }
    }
    myFile.close();
}


vector<int> Decompressor::decode(string in)
{
    ifstream infile;
    char c;
    infile.open(in, ios::binary | ios::in);
    vector<int> chars;
    infile.read(&c, 1);
    ENCODING_LENGTH = c ;
    long charCpt = 0;

    string s = "", temp = "";
    int n = 0;
    while(!infile.eof()) {
        infile.read(&c, 1);
        charCpt++;
        float f = (float)charCpt / (float)size;
        if(f * 10 > nbBar) {
            nbBar++;
            Utils::drawProgressBar("decompressing : ", nbBar);
        }
        s += bitset<8>(c + 0).to_string();
        //cout << "l : " << bitset<8>(c + 127).to_string() << endl;
        if(s.size() > ENCODING_LENGTH) {
            temp = s.substr(ENCODING_LENGTH, s.size() - ENCODING_LENGTH);
            s = s.substr(0, ENCODING_LENGTH);
            chars.push_back(bitset<512>(s).to_ulong());
            s = temp;
        }
    }
    /*for( std::vector<int>::const_iterator i = chars.begin(); i != chars.end(); ++i)
        std::cout << *i << ' ';
    cout << endl;*/
    return chars;
}

void Decompressor::initDico()
{
    for (int var = 0; var < 256; ++var) {
        char c = var;
        stringstream ss;
        ss << c;
        m.push_back(ss.str());
    }
}

string Decompressor::pair(string x, char y)
{
    stringstream ss;
    string s;
    ss << y;
    return x + y;
}

