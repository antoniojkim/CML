#ifndef __READIDX__
#define __READIDX__

#include <fstream>
#include <cstdlib>
#include <string>

uint32_t read_u32(std::istream& f){
    uint32_t val;
    uint8_t bytes[4];
    f.read((char*)bytes, 4);

    val = bytes[3] | (bytes[2] << 8) | (bytes[1] << 16) | (bytes[0] << 24);
    
    return val;
}
uint8_t read_u8(std::istream& f){
    uint8_t val;
    uint8_t bytes[1];
    f.read((char*)bytes, 1);
    
    val = bytes[0];
    return val;
}

template<int N>
struct IDX {
    int* data = nullptr;
    int numDims = N;
    int dims[N];
    int size = -1;
     
    ~IDX(){ delete[] data; }
    int& operator[](int index){
        if (index >= 0 && index < size){
            return data[index];
        }
        throw "Invalid Index in IDX";
    }
};

template<int N>
IDX<N> readIDXFile(const std::string& file){
    std::ifstream f (file, std::ios::in | std::ios::binary);
    int magicNumber = read_u32(f);
    IDX<N> idx;
    idx.size = 1;
    for (int i = 0; i<N; ++i){
        idx.dims[i] = read_u32(f);
        idx.size *= idx.dims[i];
    }
    idx.data = new int[idx.size];
    for (int i = 0; i<idx.size; ++i){
        idx.data[i] = read_u8(f);
    }
    return idx;
}

// MNIST data can be downloaded here:  http://yann.lecun.com/exdb/mnist/

inline IDX<1> readMNISTTrainingSetLabelFile(){
    return readIDXFile<1>("data/train-labels-idx1-ubyte");
}   
inline IDX<1> readMNISTTestSetLabelFile(){
    return readIDXFile<1>("data/t10k-labels-idx1-ubyte");
}

inline IDX<3> readMNISTTrainingSetImageFile(){
    return readIDXFile<3>("data/train-images-idx3-ubyte");
}   
inline IDX<3> readMNISTTestSetImageFile(){
    return readIDXFile<3>("data/t10k-images-idx3-ubyte");
}

#endif // __READIDX__