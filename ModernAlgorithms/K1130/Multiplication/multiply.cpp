#include <cstdint>
#include <iostream>
#include <fstream>
#include <cmath>

void multiply(const uint8_t * a, const uint8_t * b, uint8_t * c, int a_rows, int a_cols, int b_rows, int b_cols) {
    for (int i = 0; i < a_rows; ++i) {
        for (int j = 0; j < b_cols; ++j) {
            for (int k = 0; k < a_cols; ++k) {
                c[i * b_cols + j] += a[i * a_cols + k] * b[k * b_cols + j];
            }
        }
    }
}

uint8_t * readBlock(std::fstream &fin, const int blockRows, const int blockCols,
                    const int rows, const int cols, const int rowsOffset, const int colsOffset, const int offset) {
    uint8_t * buffer = new uint8_t [blockRows * blockCols];
    if (blockCols == cols) {
        fin.read((char *)buffer, blockRows * blockCols);
    } else {
        for (int i = 0; i < blockRows; i++) {
            int seek = (rowsOffset + i) * cols + colsOffset + offset;
            fin.seekg(seek, std::ios_base::beg);
            fin.read((char *)buffer + i * blockCols, blockCols);
        }
    }
    return buffer;
}

void writeBlock(std::fstream &fout, const uint8_t *buffer, const int blockRows, const int blockCols,
                const int rows, const int cols,
                const int rowsOffset, const int colsOffset, const int offset) {
    if (blockCols == cols) {
        fout.write((char *)buffer, blockCols * blockRows);
    } else {
        for (int i = 0; i < blockRows; i++) {
            int seek = (rowsOffset + i) * cols + colsOffset + offset;
            fout.seekp(seek, std::ios_base::beg);
            fout.write((char *)buffer + i * blockCols, blockCols);
        }
    }
}

int main() {
    std::fstream fin("input.bin", std::fstream::in | std::fstream::binary);
    std::fstream fout("output.bin", std::fstream::out | std::fstream::binary);
    fout.clear();
    uint32_t sizeN = 0;
    uint32_t sizeM = 0;
    
    //uint32_t blockSize = 300;
    
    fin.read((char *)&sizeN, sizeof(sizeN));
    fin.read((char *)&sizeM, sizeof(sizeM));
    //uint32_t size = std::min(sizeN,sizeM);
    
    //if (size < blockSize) {
    //    blockSize = size;
    //}
    
    for (int i = 0; i < sizeN;  i += sizeN) {
        int a_rows = sizeN;
        for (int j = 0; j < sizeM;  j += sizeM) {
            int b_cols = 1; //1
            uint8_t * c_block = new uint8_t [a_rows * b_cols];
            std::fill(c_block, c_block + a_rows * b_cols, 0);
            
            for (int k = 0; k < sizeN;  k += sizeN) {//!!!! size
                int a_cols = sizeM;
                int b_rows = sizeM;
                uint8_t * a_block = readBlock(fin, a_rows, a_cols, sizeN, sizeM, i, k, 8);
                uint8_t * b_block = readBlock(fin, b_rows, b_cols, sizeM, 1, k, j, 8 + sizeN * sizeM);
                multiply(a_block, b_block, c_block, a_rows, a_cols, b_rows, b_cols);
                
                delete a_block;
                delete b_block;
            }
            
            writeBlock(fout, c_block, a_rows, b_cols, a_rows, b_cols, i, j, 0);
            delete[] c_block;
        }
    }
    
    fin.close();
    fout.close();
    return 0;
}
