#include "utils.h"

Utils::Utils()
{
}

void Utils::drawProgressBar(string info, int nbBar)
{
    if(nbBar > 100) nbBar = 100;
    string s = info + to_string(nbBar) + "%";
    //cout << s << '\r' << flush;

}

long Utils::getFileSize(string fileName)
{
    ifstream file(fileName, ifstream::in | ifstream::binary);

    if(!file.is_open())
    {
        cout << "could not open file : " << fileName << endl;
        return -1;
    }

    file.seekg(0, ios::end);
    int fileSize = file.tellg();
    file.close();

    return fileSize;
}
