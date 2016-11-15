#include <iostream>
#include <stdlib.h>
#include <fstream>
using namespace std;


void Read_file(fstream&f, string filename)
{
       uint64_t x;
       cout << endl;
       f.open(filename, ios::in|ios::binary);
       if(f.is_open())
       {
             if(f.eof())
             {
                    f.clear();
                    f.seekg(0);
             }
             cout << "Content of : " << filename << endl;
             while(f.read((char*)&x, sizeof x))
             {
                    cout << x << " " ;
             }
       }
       else
       {
             cout << "Error opening file" << endl;
             exit(1);
       }
       cout << endl;
       f.close();
}

int main () {
  fstream f1;
  Read_file(f1, "output.bin");
  return 0;
}