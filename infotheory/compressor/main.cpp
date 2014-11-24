#include <iostream>
#include "compressor.h"
#include "decompressor.h"
using namespace std;

int main()
{
    Compressor c;
    //cout << "compressing" << endl;
    c.compress("/home/noe/Téléchargements/2.txt", "/home/noe/Téléchargements/compc");
    cout << endl;
    Decompressor d;
    //cout << "decompressing" << endl;
    d.decompress("/home/noe/Téléchargements/compc", "/home/noe/Téléchargements/outc.txt");
    cout << endl;
    return 0;
}

