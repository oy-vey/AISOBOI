#include <fstream>
#include <string>
#include <vector>
#include <stdint.h>
#include <cstring>
#include <stdio.h>
#include <ctime>
using namespace std;


typedef uint32_t size;

const size Block = 300; 

struct MatrixSize {
    size N;
    size M;
};

MatrixSize Transpose(const vector<char>& in, const MatrixSize& ms, vector<char>& out) {
    MatrixSize transposedMs;
    transposedMs.N = ms.M;
    transposedMs.M = ms.N;

    for (size i = 0; i < ms.N; ++i) {
        for (size j = 0; j < ms.M; ++j) {
            out[j * ms.N + i] = in[i * ms.M + j];
        }
    }

    return transposedMs;
}

void TransposeAndWrite(ofstream& out, const MatrixSize& initMs,
    const MatrixSize& msRead, const vector<char>& matrix, size i_b, size j_b)
{
    vector<char> transposedMatrix(Block * Block);
    const MatrixSize trMs = Transpose(matrix, msRead, transposedMatrix);
    MatrixSize initTrMs;
    initTrMs.M = initMs.N;
    initTrMs.N = initMs.M;

    const size blocksInRow = (initTrMs.M + Block - 1) / Block;

    if (blocksInRow == 1) {
        out.write(&transposedMatrix[0], trMs.N * trMs.M);
    } else {
        for (size i = 0; i < trMs.N; ++i) {
            out.seekp(8 + (j_b + i) * initTrMs.M + i_b);
            out.write(&transposedMatrix[i * trMs.M], trMs.M);
        }
    }
}


int main() {
    ifstream in("input.bin", ios::binary);
    ofstream out("output.bin", ios::binary);
	
    MatrixSize ms;
    {
        char bufferN[4];
		char bufferM[4];
        in.read(bufferN, 4);
        memcpy(&ms.N, bufferN, 4);
        in.read(bufferM, 4);
        memcpy(&ms.M, bufferM, 4);
        out.write(bufferM, 4);
        out.write(bufferN, 4);
    }
	    
	MatrixSize msRead;
	vector<char> matrix(Block * Block);
	
	const size blocksInRow = (ms.M + Block - 1) / Block;
	const size blocksInCol = (ms.N + Block - 1) / Block;
	
 if (blocksInRow * blocksInCol == 1) {
        in.read(&matrix[0], ms.N * ms.M);
        msRead.N = ms.N;
        msRead.M = ms.M;
        TransposeAndWrite(out, ms, msRead, matrix, 0, 0);

    } else if (blocksInRow == 1) {
        const size numOfRowsInMemory = Block * Block/ ms.M;
        const size sizeOfEachMatrix = numOfRowsInMemory * ms.M;
        msRead.M = ms.M;
        for (size i_b = 0; i_b < ms.N * ms.M; i_b += sizeOfEachMatrix) {
            const size bytesToRead = std::min(sizeOfEachMatrix, ms.N * ms.M - i_b);
            in.read(&matrix[0], bytesToRead);
            msRead.N = bytesToRead / msRead.M;
            TransposeAndWrite(out, ms, msRead, matrix, i_b / ms.M, 0);
        }
    } else {
        for (size i_b = 0; i_b < ms.N; i_b += Block) {
            msRead.N = std::min(Block, ms.N - i_b);
            for (size j_b = 0; j_b < ms.M; j_b += Block) {
                msRead.M = std::min(Block, ms.M - j_b);
                for (size i = 0; i < msRead.N; ++i) {
                    in.seekg(8 + (i_b + i) * ms.M + j_b);
                    in.read(&matrix[i * msRead.M], msRead.M);
                }
                TransposeAndWrite(out, ms, msRead, matrix, i_b, j_b);
            }
        }
    }
    return 0;
}