// C++ program to implement external sorting using
// merge sort
#define __STDC_FORMAT_MACROS 1
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <climits>
#include <algorithm>
#include <fstream>
#include <cmath>
#pragma warning(disable: 4996)


using namespace std;

template<typename T>
inline void Write(T val, std::ofstream& out) {
    out.write((char*)&val, sizeof(T));
}


struct MinHeapNode
{
    // The element to be stored
    uint64_t element;
    
    // index of the array from which the element is taken
    int i;
};

// Prototype of a utility function to swap two min heap nodes
void swap(MinHeapNode* x, MinHeapNode* y);

// A class for Min Heap
class MinHeap
{
    MinHeapNode* harr; // pointer to array of elements in heap
    int heap_size;     // size of min heap
    
public:
    // Constructor: creates a min heap of given size
    MinHeap(MinHeapNode a[], int size);
    
    // to heapify a subtree with root at given index
    void MinHeapify(int);
    
    // to get index of left child of node at index i
    int left(int i) { return (2 * i + 1); }
    
    // to get index of right child of node at index i
    int right(int i) { return (2 * i + 2); }
    
    // to get the root
    MinHeapNode getMin() { return harr[0]; }
    
    // to replace root with new node x and heapify()
    // new root
    void replaceMin(MinHeapNode x)
    {
        harr[0] = x;
        MinHeapify(0);
    }
};

// Constructor: Builds a heap from a given array a[]
// of given size
MinHeap::MinHeap(MinHeapNode a[], int size)
{
    heap_size = size;
    harr = a; // store address of array
    int i = (heap_size - 1) / 2;
    while (i >= 0)
    {
        MinHeapify(i);
        i--;
    }
}

// A recursive method to heapify a subtree with root
// at given index. This method assumes that the
// subtrees are already heapified
void MinHeap::MinHeapify(int i)
{
    int l = left(i);
    int r = right(i);
    int smallest = i;
    if (l < heap_size && harr[l].element < harr[i].element)
        smallest = l;
    if (r < heap_size && harr[r].element < harr[smallest].element)
        smallest = r;
    if (smallest != i)
    {
        swap(&harr[i], &harr[smallest]);
        MinHeapify(smallest);
    }
}

// A utility function to swap two elements
void swap(MinHeapNode* x, MinHeapNode* y)
{
    MinHeapNode temp = *x;
    *x = *y;
    *y = temp;
}




// Merges k sorted files.  Names of files are assumed
// to be 1, 2, 3, ... k
void mergeFiles(char *output_file, char *input_file, uint64_t run_size)
{
    
    // FINAL OUTPUT FILE
    fstream f;
    f.open(input_file, ios::in | ios::binary);
    uint64_t elements;
    f.read((char *)&elements, sizeof(elements));
    f.close();
    ofstream output(output_file, std::fstream::out | std::fstream::binary);
    output.write((char*)&elements, sizeof(elements));
    
    
    
    
    double a = elements/(double)run_size;
    
    int k = ceil(a);
    //int real_num_size = min(elements, run_size);
    FILE* in[k];
    for (int i = 0; i < k; i++)
    {
        char fileName[4];
        
        // convert i to string
        snprintf(fileName, sizeof(fileName), "%d", i);
        
        // Open output files in read mode.
        in[i] = fopen(fileName, "r");
    }
    
    
    
    
    // Create a min heap with k heap nodes.  Every heap node
    // has first element of scratch output file
    MinHeapNode* harr = new MinHeapNode[k];
    int i;
    for (i = 0; i < k; i++)
    {
        // break if no output file is empty and
        // index i will be no. of input files
        if (fscanf(in[i], "%" PRIu64, &harr[i].element) != 1)
            break;
        
        harr[i].i = i; // Index of scratch output file
    }
    MinHeap hp(harr, i); // Create the heap
    
    int count = 0;
    
    // Now one by one get the minimum element from min
    // heap and replace it with next element.
    // run till all filled input files reach EOF
    while (count != i)
    {
        // Get the minimum element and store it in output file
        MinHeapNode root = hp.getMin();
        Write<uint64_t>(root.element, output);
        
        // Find the next element that will replace current
        // root of heap. The next element belongs to same
        // input file as the current min element.
        if (fscanf(in[root.i], "%" PRIu64, &root.element) != 1)
        {
            root.element = pow(2, 60);
            count++;
        }
        
        // Replace root with next element of input file
        hp.replaceMin(root);
    }
    
    // close input and output files
    for (int i = 0; i < k; i++)
        fclose(in[i]);
    
    output.close();
}

// Using a merge-sort algorithm, create the initial runs
// and divide them evenly among the output files
void createInitialRuns(char *input_file, uint64_t run_size)
{
    // For big input file
    fstream f;
    f.open(input_file, ios::in | ios::binary);
    uint64_t elements;
    f.read((char *)&elements, sizeof(elements));
    double a = elements/(double)run_size;
    
    int num_ways = ceil(a);
    int real_num_size = min(elements, run_size);
    
    // output scratch files
    FILE* out[num_ways];
    char fileName[4];
    for (int i = 0; i < num_ways; i++)
    {
        // convert i to string
        snprintf(fileName, sizeof(fileName), "%i", i);
        
        // Open output files in write mode.
        out[i] = fopen(fileName, "w");
    }
    
    // allocate a dynamic array large enough
    // to accommodate runs of size run_size
    uint64_t * arr = new uint64_t[real_num_size];
    
    bool more_input = true;
    int next_output_file = 0;
    
    int i = 0;
    
    
    //ifstream input(input_file, ifstream::in | ifstream::binary);
    
    while (more_input)
    {
        
        // write run_size elements into arr from input file
        
        i = 0;
        more_input = false;
        while (i < real_num_size && f.read((char*)&arr[i], sizeof(elements))) // each 4th brings 4KB
        {
            more_input = true;
            ++i;
        }
        if (more_input == false) { break; };
        
        // sort array using merge sort
        sort(arr, arr + i);
        
        // write the records to the appropriate scratch output file
        // can't assume that the loop runs to run_size
        // since the last run's length may be less than run_size
        for (int j = 0; j < i; j++)
            
            fprintf(out[next_output_file], "%" PRIu64 "\n", arr[j]);// Replace
        
        next_output_file++;
    }
    
    // close input and output files
    for (int i = 0; i < num_ways; i++)
        fclose(out[i]);
    
    f.close();
    
}

// For sorting data stored on disk
void externalSort(char* input_file, char *output_file, uint64_t run_size)
{
    // read the input file, create the initial runs,
    // and assign the runs to the scratch output files
    createInitialRuns(input_file, run_size);
    
    // Merge the runs using the K-way merging
    mergeFiles(output_file, input_file, run_size);
}


// Driver program to test above
int main()
{
    
    // The size of each partition
    uint64_t run_size = 38000; // 128000
    
    
    char input_file[] = "input.bin";
    char output_file[] = "output.bin";
    
    
    externalSort(input_file, output_file, run_size);
    
    return 0;
}
