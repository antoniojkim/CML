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
    void read_t(std::istream& f, cml::DMatrix<T>& data, std::vector<int>& dims, const int& N, const int& R){
        if (data.rows() != N || data.cols() != R){
            data.resize(N, R);
        }
        
        U d;
        for (int n = 0; n < N; ++n){
            for (int r = 0; r < R; ++r){
                read_U(f, d);
                data(n, r) = d;
            }
        }
    }
    
    template<typename T, template<typename> class TensorType>
    cml::tensor<T> read(std::istream& f){
        uint32_t magicNumber = read_u32(f);
        
        unsigned int numDims = ((magicNumber) & 0xff);
        std::vector<int> dims;
        dims.reserve(numDims);
        int N = 0, R = 1;
        for (unsigned int i = 0; i < numDims; ++i){
            dims.emplace_back(read_u32(f));
            if (i == 0){
                N = dims[i];
            }
            else {
                R *= dims[i];
            }
        }

        cml::tensor<T> data = std::make_shared<TensorType<T>>(dims);
        
        switch((magicNumber >> 8) & 0xff){
            case 0x08:
                read_t<T, uint8_t>(f, data->data(), dims, N, R);
                break;
            case 0x09:
                read_t<T, int8_t>(f, data->data(), dims, N, R);
                break;
            case 0x0B:
                read_t<T, short>(f, data->data(), dims, N, R);
                break;
            case 0x0C:
                read_t<T, int>(f, data->data(), dims, N, R);
                break;
            case 0x0D:
                read_t<T, float>(f, data->data(), dims, N, R);
                break;
            case 0x0E:
                read_t<T, double>(f, data->data(), dims, N, R);
                break;
            default:
                throw "Invalid data type";
        }
        
        return data;
    }
    
}

#endif // __CML_UTILS_DATAFORMATS_IDX_H__