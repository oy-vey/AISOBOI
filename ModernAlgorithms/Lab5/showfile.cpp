#include <cstdint>
#include <iostream>
#include <fstream>
#include <cmath>

int main() {
     char filename[20];
    std::cin >> filename;
    std::ifstream fin(filename, std::ifstream::in | std::ifstream::binary);

    uint64_t elements = 0;
    //std::cout << sizeof(elements) << std::endl;

    fin.read((char *)&elements, sizeof(elements));
    std::cout << elements << std::endl;

    uint64_t * buffer = new uint64_t [elements];
    fin.read((char *)buffer, elements * sizeof(elements));//Extracts elements2 characters from the stream and stores them in the array pointed to by s.
    fin.close();
    for (int j = 0; j < elements; j++) {
        std::cout << buffer[j] <<' '<< sizeof(buffer[j] ) << std::endl;
    }
     //   std::cout << std::endl;
    return 0;
}