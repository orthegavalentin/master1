#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class Utils
{
public:
    Utils();
    static void drawProgressBar(string info, int nbBar);
    static long getFileSize(string fileName);

};

#endif // UTILS_H
