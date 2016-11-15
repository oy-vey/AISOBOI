#include <cstdint>
#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>


template<typename T>
inline void Write(T val, std::ofstream& out) {
  out.write((char*)&val, sizeof(T));
}



int main() {

  std::ifstream fin("input.bin", std::ifstream::in | std::ifstream::binary);

  uint64_t elements = 0;  

  fin.read((char *)&elements, sizeof(elements));


  uint64_t * buffer = new uint64_t [elements];
  fin.read((char *)buffer, elements * sizeof(elements));//Extracts elements2 characters from the stream and stores them in the array pointed to by s.
  fin.close();


  std::sort(buffer, buffer+elements);


  std::ofstream out("output.bin", std::fstream::out | std::fstream::binary);
  Write(elements, out);
  for (uint64_t iter = 0; iter < elements; ++iter) {
    //uint64_t r = rand()%(max-min + 1) + min;
    //std::cout << "Random" << iter << '=' << r << std::endl;
    Write<uint64_t>(buffer[iter], out);
  }

    out.close();
    return 0;
}