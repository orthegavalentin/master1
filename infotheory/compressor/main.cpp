#include <iostream>
#include "compressor.h"
#include "decompressor.h"
using namespace std;

int main()
{
    Compressor c;
    //cout << "compressing" << endl;
    //c.compress("/auto_home/nlephilippe/Téléchargements/1.txt", "/auto_home/nlephilippe/Téléchargements/compc");
    c.compress("/home/noe/Téléchargements/1.png", "/home/noe/Téléchargements/compc");
    cout << endl;
    Decompressor d;
    //cout << "decompressing" << endl;
    //d.decompress("/auto_home/nlephilippe/Téléchargements/compc", "/auto_home/nlephilippe/Téléchargements/outc.txt");
    d.decompress("/home/noe/Téléchargements/compc", "/home/noe/Téléchargements/outc.png");
    cout << endl;
    return 0;
}

