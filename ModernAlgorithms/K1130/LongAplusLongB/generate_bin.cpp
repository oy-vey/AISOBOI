#include <cstdint>
#include <fstream>
#include <iostream>

template<typename T>
inline void Write(T val, std::ofstream& out) {
	out.write((char*)&val, sizeof(T));
}

int main(int argc, char* argv[]) {


	uint32_t N = static_cast<uint32_t>(atoi(argv[1]));
	uint32_t M = static_cast<uint32_t>(atoi(argv[2]));

	std::ofstream out("input.bin", std::fstream::out | std::fstream::binary);
	Write(N, out);
	for (uint32_t iter = 1; iter <= N; ++iter) {
		Write<uint8_t>(iter , out);
	}
	Write(M, out);
	for (uint32_t iter = 1; iter <= M; ++iter) {
			Write<uint8_t>(iter , out);
	}
	out.close();
	return 0;
}