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
    vector<int>* decoded = decode(in);
    vector<int> chars;

    for(const auto& e : *decoded) {
        //cout << "chars.push_back(" << e << ");" << endl;
        int n = e;
        chars.push_back(n);
    }

    w = (char)chars.at(0);
    size = chars.size();
    myFile << w;
    string entry;
    nbBar = 0;

    string s;
    for (long var = 1; var < chars.size() - 1; ++var) {
        //cout << "[decompress] : " << chars->at(var) << endl;
        float f = (float)var / (float)size;
        if(f * 100 > nbBar) {
            nbBar++;
            Utils::drawProgressBar("decompressing : ", nbBar);
        }

        if(m.size() >= pow(2, ENCODING_LENGTH)) {
            m.clear();
            initDico();
        }
        k = chars.at(var);
        //cout << k << endl;
        //cout << m.size() << endl;
        if(k < m.size()) {
            entry = m.at(k);
            s += entry;
            //myFile << entry;
            m.push_back(w + entry.at(0));
            w = entry;
        } else {
            entry = w + w.at(0);
            s += entry;
            //myFile << entry;
            m.push_back(entry);
            w = entry;
        }
    }
    //cout << s << endl;
    s = s.substr(0, s.size() - 1);
    myFile << s;
    myFile.close();
}

vector<int>* Decompressor::decompressRegular(ifstream* infile, int ENCODING_LENGTH)
{

    this->ENCODING_LENGTH = ENCODING_LENGTH;
    vector<int>* chars = new vector<int>;
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
            chars->push_back(bitset<512>(s).to_ulong());
            s = temp;
        }
    }

    return chars;
}

vector<int>* Decompressor::parseHuffman(ifstream *infile)
{
    map<long, int> *m = new map<long, int>;
    string s = "";
    long long size = 8;
    char c;
    string temp = "";
    int key = -1;
    int value = -1;
    int last = -1;
    char next;
    cout << "[parseHuffman] dico : ";
    while(!infile->eof()) {
        infile->read(&c, 1);
        size += 8;
        if(last == 0 && (int) c == 0) {
            infile->read(&next, 1);
            if(next == 0) {
                cout << "dico size : " << size + 8 << endl;
                //infile->read(&next, 1);
                return decompressHuffman(infile, new Huffman(m));
            } else {
                infile->putback(next);
            }
        }
        s += bitset<8>(c).to_string();
        //cout << bitset<8>(last).to_string();
        last = c;
        if(s.size() > ENCODING_LENGTH) {
            temp = s.substr(ENCODING_LENGTH, s.size());
            s = s.substr(0, ENCODING_LENGTH);
            int n = std::bitset<512>(s).to_ulong();
            s = temp;
            if(key == -1) key = n;
            else value = n;
        }

        if(key != -1 && value != -1) {

           // cout << "key : " << key << endl;
           // cout << "value : " << value << endl;

            m->insert(std::pair<long, int>(key, value));
            value = -1;
            key = -1;
        }
    }
}

vector<int>* Decompressor::decompressHuffman(ifstream *infile, Huffman *h)
{
    vector<bool> *v = new vector<bool>;
    char c;

    //cout << "[decompressHuffman] data : ";
    infile->read(&c, 1);
    while(!infile->eof()) {
       bitset<8> bit((int) c);
        //cout << "*****" << endl,
        //cout << bit.to_string() << endl;
        for (int var = bit.size() - 1; var >= 0; --var) {
            v->push_back(bit[var]);
            //cout << bit[var];
        }
        infile->read(&c, 1);
    }
    cout << endl;
    return h->convertToChars(v);
}

vector<int>* Decompressor::decode(string in)
{
    ifstream *infile = new ifstream;
    char c;
    infile->open(in, ios::binary | ios::in);
    infile->read(&c, 1);
    std::bitset<8> bit(c);
    string s = bit.to_string();
    cout << s << endl;
    if(!s.substr(0, 1).compare("0")) {
        cout << "regular compression" << endl;
        return decompressRegular(infile, (int) c);
    } else {
        cout << "huffman compression" << endl;
        bit[7] = 0;
        ENCODING_LENGTH = bit.to_ulong();
        return parseHuffman(infile);
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

