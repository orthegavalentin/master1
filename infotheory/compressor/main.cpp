#include <iostream>
#include "compressor.h"
#include "decompressor.h"
using namespace std;

int main()
{
    Compressor c;
    cout << "compressing" << endl;
    c.compress("/home/noe/Téléchargements/1.png", "/home/noe/Téléchargements/compc");
    cout << "done" << endl;
    Decompressor d;
    cout << "decompressing" << endl;
    d.decompress("/home/noe/Téléchargements/compc", "/home/noe/Téléchargements/outc.png");
    cout << "done" << endl;
    char u = -13 + 127;
    cout << "c : " << u << endl;
    return 0;
}

