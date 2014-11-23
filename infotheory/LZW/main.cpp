#include <iostream>
#include <fstream>

#include <compressor.h>
using namespace std;

int main () {
  char buffer;
  ifstream infile;
  infile.open("/home/noe/Téléchargements/test.txt", ios::binary | ios::in);
  while(!infile.eof()) {
    infile.read(&buffer, 1);
    cout << buffer << endl;
  }
}
