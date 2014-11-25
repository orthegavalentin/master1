#include "utils.h"

Utils::Utils()
{
}

void Utils::drawProgressBar(string info, int nbBar)
{
    string s = info + "<";
    for (int var = 0; var < 10; ++var) {
        if(var < nbBar) {
            s += "=";
        } else {
            s += " ";
        }
    }
    s += ">";
    cout << s << '\r' << flush;

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
