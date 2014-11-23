#include "decompressor.h"

Decompressor::Decompressor()
{
    result = "";
    initDico();
}

void Decompressor::decompress(string in, string out)
{
    ofstream myFile;
    myFile.open(out, ios::out | ios::binary);
    string e = "";
    vector<int> chars = decode(in);
    //cout << chars.size() << endl;
    prevcode = chars[0];
    myFile << (char) prevcode;
    for (long var = 1; var < chars.size(); ++var) {
        //cout << var << endl;
        if(m.size() >= pow(2, ENCODING_LENGTH)) {
            cout << "to big clearing dico" << endl;
            m.clear();
            initDico();
        }
        currcode = chars[var];
        if(currcode >= m.size()) {
            e = e.substr(0, 1);
        } else {
            e = m.at((int)currcode);
        }
        myFile << e;
        //cout << e;
        result += e;
        ch = e.at(0);
        //cout << e.at(0);
        //cout << m[(int) prevcode] + ch << endl;
        string s = m.at((int) prevcode) + (char)ch;
        m.push_back(s);
        prevcode = currcode;
    }
    cout << "r : " << result << endl;
    myFile.close();
}


vector<int> Decompressor::decode(string in)
{
    ifstream infile;
    char c;
    infile.open(in, ios::binary | ios::in);
    vector<int> chars;
    infile.read(&c, 1);
    ENCODING_LENGTH = c + 127;

    string s = "", temp = "";
    int n = 0;
    while(!infile.eof()) {
        infile.read(&c, 1);
        s += bitset<8>(c + 127).to_string();
        //cout << "l : " << bitset<8>(c + 127).to_string() << endl;
        if(s.size() > ENCODING_LENGTH) {
            temp = s.substr(ENCODING_LENGTH, s.size() - ENCODING_LENGTH);
            s = s.substr(0, ENCODING_LENGTH);

            chars.push_back(bitset<512>(s).to_ulong());
            //cout << chars[chars.size() - 1] << endl;
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

