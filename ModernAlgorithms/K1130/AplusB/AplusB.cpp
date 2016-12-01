#include <fstream>

using namespace std;
int main () {
    char input_file[] = "input.bin";
    char output_file[] = "output.bin";

    uint32_t A, B, C;
    fstream input;

    input.open(input_file, ios::in | ios::binary);
    input.read((char *)&A, sizeof(A));
    input.read((char *)&B, sizeof(B));
    input.close();

    C = A + B;
    
    ofstream output(output_file, std::fstream::out | std::fstream::binary);
    output.write((char*)&C, sizeof(C));
    output.close();

    return 0;

}