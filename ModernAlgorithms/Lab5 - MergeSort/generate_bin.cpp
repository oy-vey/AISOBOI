#include <cstdint>
#include <fstream>
#include <iostream>

template<typename T>
inline void Write(T val, std::ofstream& out) {
	out.write((char*)&val, sizeof(T));
}

int main(int argc, char* argv[]) {


	uint64_t N = static_cast<uint64_t>(atoi(argv[1]));

	std::ofstream out("input.bin", std::fstream::out | std::fstream::binary);
	Write(N, out);
	for (uint64_t iter = 1; iter <= N; ++iter) {
		Write<uint64_t>(iter, out);
	}
	out.close();
	return 0;
}