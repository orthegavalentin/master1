#include <iostream>
#include <fstream>
#include <string>
<<<<<<< HEAD

using namespace std;

int main(int argc, char* argv[]) {
  streampos size;
  char * memblock;

  ifstream file ("example.bin", ios::in|ios::binary|ios::ate);
  if (file.is_open()) {
    size = file.tellg();
    memblock = new char [size];
    file.seekg (0, ios::beg);
    file.read (memblock, size);
    file.close();

    cout << "the entire file content is in memory";

    delete[] memblock;
  }
  else cout << "Unable to open file";
  return 0;
=======
using namespace std;

int compress (string file) {
  char buffer;
  ifstream infile;
  infile.open(file, ios::binary | ios::in);
  while(!infile.eof()) {
    infile.read(&buffer, 1);
    cout << buffer << endl;
  }
>>>>>>> 92f8eb89be046030a6032f59fd5449c76aa73f77
}
