#include <iostream>
#include "compressor.h"
#include "decompressor.h"
using namespace std;

int main()
{
    Compressor c;
    //cout << "compressing" << endl;
<<<<<<< Updated upstream
    c.compress("/auto_home/nlephilippe/Téléchargements/1.txt", "/auto_home/nlephilippe/Téléchargements/compc");
    cout << endl;
    Decompressor d;
    //cout << "decompressing" << endl;
    d.decompress("/auto_home/nlephilippe/Téléchargements/compc", "/auto_home/nlephilippe/Téléchargements/outc.txt");
=======
    c.compress("/auto_home/nlephilippe/Téléchargements/redman", "/auto_home/nlephilippe/Téléchargements/compc");
    cout << endl;
    Decompressor d;
    //cout << "decompressing" << endl;
    d.decompress("/auto_home/nlephilippe/Téléchargements/compc", "/auto_home/nlephilippe/Téléchargements/outc");
>>>>>>> Stashed changes
    cout << endl;
    return 0;
}

