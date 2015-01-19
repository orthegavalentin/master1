#include <iostream>
#include "compressor.h"
#include "decompressor.h"
using namespace std;

int main()
{
    Compressor c;
    //cout << "compressing" << endl;
//    c.compress("/auto_home/nlephilippe/Téléchargements/test1.txt", "/auto_home/nlephilippe/Téléchargements/compc");
    c.compress("/home/noe/Téléchargements/test1.txt", "/home/noe/Téléchargements/compc");
  //  cout << endl;
    Decompressor d;
    //cout << "decompressing" << endl;
    //d.decompress("/auto_home/nlephilippe/Téléchargements/compc", "/auto_home/nlephilippe/Téléchargements/outc.bin");
//    d.decompress("/home/noe/Téléchargements/out.bin", "/home/noe/Téléchargements/outc.txt");
    cout << endl;
    return 0;
}

