#include <cstdint>
#include <fstream>
#include <iostream>
#include <random>
#include <math.h>

template<typename T>
inline void Write(T val, std::ofstream& out) {
	out.write((char*)&val, sizeof(T));
}

int main(int argc, char* argv[]) {
	

	uint64_t elements = 10;
	uint64_t min = 1;
	uint64_t max = pow(2, 60);

	

	std::ofstream out("input.bin", std::fstream::out | std::fstream::binary);
	Write(elements, out);
	for (uint64_t iter = 1; iter <= elements; ++iter) {
		uint64_t r;
		std::cin >> r;
		//std::cout << "Random" << iter << '=' << r << std::endl;
		Write(r, out);
	}

	out.close();
	return 0;
}