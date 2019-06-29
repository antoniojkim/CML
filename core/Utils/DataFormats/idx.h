#ifndef __CML_UTILS_DATAFORMATS_IDX_H__
#define __CML_UTILS_DATAFORMATS_IDX_H__

#include <cstdlib>
#include <iostream>
#include <iomanip>

#include "../../CML/Tensor.h"
#include "tools.h"

namespace idx {
    
    uint32_t read_u32(std::istream& f){
        uint32_t val;
        uint8_t bytes[4];
        f.read((char*)bytes, 4);

        val = bytes[3] | (bytes[2] << 8) | (bytes[1] << 16) | (bytes[0] << 24);

        return val;
    }
    
    template<typename U>
    inline void read_U(std::istream& f, U& d){
        if (f.good()){
            f.read((char *)&d, sizeof(U));
        }
        else {
            throw "Invalid IDX read";
        }
    }
    
    template<typename T, typename U>
    void read_t(std::istream& f, DMatrix<T>& data, int* dims, const int& R, const int& C){
        if (data.rows() != R || data.cols() != C){
            data.resize(R, C);
        }
        
        U d;
        for (int r = 0; r < R; ++r){
            for (int c = 0; c < C; ++c){
                read_U(f, d);
                data(r, c) = d;
            }
        }
    }
    
    template<typename T>
    void read(std::istream& f, DMatrix<T>& data){
        uint32_t magicNumber = read_u32(f);
        
        unsigned int numDims = ((magicNumber) & 0xff);
        int* dims = new int[numDims];
        int R, C = 1;
        for (unsigned int i = 0; i < numDims; ++i){
            dims[i] = read_u32(f);
            if (i == 0){
                R = dims[i];
            }
            else {
                C *= dims[i];
            }
        }
        
        switch((magicNumber >> 8) & 0xff){
            case 0x08:
                read_t<T, uint8_t>(f, data, dims, R, C);
                break;
            case 0x09:
                read_t<T, int8_t>(f, data, dims, R, C);
                break;
            case 0x0B:
                read_t<T, short>(f, data, dims, R, C);
                break;
            case 0x0C:
                read_t<T, int>(f, data, dims, R, C);
                break;
            case 0x0D:
                read_t<T, float>(f, data, dims, R, C);
                break;
            case 0x0E:
                read_t<T, double>(f, data, dims, R, C);
                break;
            default:
                throw "Invalid data type";
        }
        
        delete[] dims;
    }
    
}

#endif // __CML_UTILS_DATAFORMATS_IDX_H__