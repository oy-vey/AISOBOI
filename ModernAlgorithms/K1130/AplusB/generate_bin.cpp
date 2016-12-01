#include <cstdint>
#include <fstream>
#include <iostream>
#include <random>
#include <cmath>
#include <time.h>

template<typename T>
inline void Write(T val, std::ofstream& out) {
	out.write((char*)&val, sizeof(T));
}

int main(int argc, char* argv[]) {
	

	uint32_t A = static_cast<uint32_t>(atoi(argv[1]));
	uint32_t B = static_cast<uint32_t>(atoi(argv[1]));	

	std::ofstream out("input.bin", std::fstream::out | std::fstream::binary);
	Write(A, out);
	Write(B, out);

	out.close();

	uint32_t C = A + B;
	    
    std::ofstream out2("realoutput.bin", std::fstream::out | std::fstream::binary);
    Write(C, out2); 
    out2.close();
	return 0;
}
