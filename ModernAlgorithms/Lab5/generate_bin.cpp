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
	

	uint64_t elements = static_cast<uint64_t>(atoi(argv[1]));
	uint64_t min = 5;
	uint64_t max = pow(2, 60);


	

	std::ofstream out("input.bin", std::fstream::out | std::fstream::binary);
	Write(elements, out);
	for (uint64_t iter = 1; iter <= elements; ++iter) {
		//srand(time(NULL));
		//uint64_t r;
		//r = rand() ;
		
		//uint64_t r;
		//std::cin >> r;
		//std::cout << "Random" << iter << '=' << max - r << std::endl;
		Write(max - iter, out);
	}

	out.close();
    
    std::ofstream out2("realoutput.bin", std::fstream::out | std::fstream::binary);
    Write(elements, out2);
    for (int iter = elements; iter > 0; --iter) {
        //srand(time(NULL));
        //uint64_t r;
        //r = rand() ;
        
        //uint64_t r;
        //std::cin >> r;
        //std::cout << "Random" << iter << '=' << max - r << std::endl;
        Write(max - iter, out2);
    }
    
    out2.close();
	return 0;
}
