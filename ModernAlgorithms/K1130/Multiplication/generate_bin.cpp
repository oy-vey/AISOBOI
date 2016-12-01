#include <cstdint>
#include <fstream>
#include <iostream>

template<typename T>
inline void Write(T val, std::ofstream& out) {
	out.write((char*)&val, sizeof(T));
}

int main(int argc, char* argv[]) {
	if (argc < 4) {
		std::cerr << "Usage: " << argv[0] << " [ROWS] [COLS] [FILENAME]" << std::endl;
		return 1;
	}

	uint32_t rows = static_cast<uint32_t>(atoi(argv[1]));
	uint32_t cols = static_cast<uint32_t>(atoi(argv[2]));
	uint32_t count = rows * cols;

	std::ofstream out(argv[3], std::fstream::out | std::fstream::binary);
	Write(rows, out);
	Write(cols, out);
	for (uint32_t iter = 1; iter <= count; ++iter) {
		Write<uint8_t>(iter % 256, out);
	}
    for (uint32_t iter = 1; iter <= cols; ++iter) {
        Write<uint8_t>(iter % 256, out);
    }

	out.close();
	return 0;
}