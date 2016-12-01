#include <cstdint>
#include <iostream>
#include <fstream>
#include <cmath>

int main() {
    std::ifstream fin("output.bin", std::ifstream::in | std::ifstream::binary);
    
    uint32_t N = 0;
    
    fin.read((char *)&N, sizeof(N));
    std::cout << N << std::endl;
    uint8_t * buffer = new uint8_t [N];
    fin.read((char *)buffer, N);
    for (int j = 0; j < N; j++) {
        std::cout << (int)buffer[j] << std::endl;
    };
    
    fin.close();
    return 0;
}
