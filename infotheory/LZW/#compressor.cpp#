#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int compress (string file) {
  char buffer;
  ifstream infile;
  infile.open(file, ios::binary | ios::in);
  while(!infile.eof()) {
    infile.read(&buffer, 1);
    cout << buffer << endl;
  }
}
