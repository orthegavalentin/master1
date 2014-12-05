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
        if(f * 100 > nbBar) {
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

vector<int> Decompressor::decompressRegular(ifstream* infile, int ENCODING_LENGTH)
{

    this->ENCODING_LENGTH = ENCODING_LENGTH;
    vector<int> chars;
    long charCpt = 0;
    char c;
    string s = "", temp = "";
    while(!infile->eof()) {
        infile->read(&c, 1);
        charCpt++;
        float f = (float)charCpt / (float)size;
        if(f * 100 > nbBar) {
            nbBar++;
            Utils::drawProgressBar("decompressing : ", nbBar);
        }
        s += bitset<8>(c).to_string();
        if(s.size() > ENCODING_LENGTH) {
            temp = s.substr(ENCODING_LENGTH, s.size() - ENCODING_LENGTH);
            s = s.substr(0, ENCODING_LENGTH);
            chars.push_back(bitset<512>(s).to_ulong());
            s = temp;
        }
    }
    return chars;
}

vector<int> Decompressor::parseHuffman(ifstream *infile)
{
    map<long, int> *m = new map<long, int>;
    string s = std::bitset<8>(0).to_string();
    char c;
    string temp = "";
    int key = -1;
    int value = -1;
    int last = 0;
    cout << "dico : 1000000010";
    while(!infile->eof()) {
        infile->read(&c, 1);
        if((int)c + last == 0) {
            cout << endl;
            return decompressHuffman(infile, new Huffman(m), temp);
        }
        last = c;
        s += bitset<8>(c).to_string();
        if(s.size() > 12) {
            temp = s.substr(12, s.size());
            s = s.substr(0, 12);
            int n = std::bitset<512>(s).to_ulong();
            if(n == 0) {
                //infile->putback(c);
                cout << "temp : " << temp << endl;
            }
            s = temp;
            if(key < 0) key = n;
            else value = n;
        }

        if(key > 0 && value > 0) {
            m->insert(std::pair<long, int>(key, value));
            value = -1;
            key = -1;
        }
    }
}

vector<int> Decompressor::decompressHuffman(ifstream *infile, Huffman *h, string temp)
{
    vector<bool> *v = new vector<bool>;
    char c;

   /* while(temp.size() > 0) {
        string s = temp;
        temp = temp.substr(1, temp.size());
        s = s.substr(0, 1);
        int n = atoi(s.c_str());
        v.push_back(n);
    }*/
    cout << "data : ";
    while(!infile->eof()) {
        infile->read(&c, 1);
        bitset<8> bit((int) c);
        cout << "*****" << endl,
        cout << bit.to_string() << endl;
        for (int var = bit.size() - 1; var >= 0; --var) {
            v->push_back(bit[var]);
            cout << bit[var];
        }
        cout << endl;
    }
    return h->convertToChars(v);
}

vector<int> Decompressor::decode(string in)
{
    ifstream infile;
    char c;
    infile.open(in, ios::binary | ios::in);
    infile.read(&c, 1);
    string s = std::bitset<8>(c).to_string();
    cout << s << endl;
    if(!s.substr(0, 1).compare("0")) {
        cout << "regular compression" << endl;
        return decompressRegular(&infile, (int) c);
    } else {
        cout << "huffman compression" << endl;
        return parseHuffman(&infile);
    }

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

