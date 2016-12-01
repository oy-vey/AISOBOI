#include <iostream>
#include <stdlib.h>
#include <fstream>
using namespace std;


void Read_file(fstream&f, string filename)
{
       uint32_t x;
       f.open(filename, ios::in|ios::binary);
       if(f.is_open())
       {
             if(f.eof())
             {
                    f.clear();
                    f.seekg(0);
             }
             //cout << "Content of : " << filename << endl;
             while(f.read((char*)&x, sizeof x))
             {
                    cout << x << endl ;
             }
       }
       else
       {
             cout << "Error opening file" << endl;
             exit(1);
       }
       f.close();
}

int main (int argc, char* argv[]) {
  fstream f1;
  Read_file(f1, argv[1]);
  return 0;
}