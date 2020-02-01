#ifndef __CML_UTILS_DATAFORMATS_IDX_H__
#define __CML_UTILS_DATAFORMATS_IDX_H__

#include <cstdlib>
#include <iostream>
#include <iomanip>

#include "../../core/Tensor.h"
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
    void read_t(std::istream& f, tensor<T> data, std::vector<size_t>& dims, const size_t& S){
        if (data->size() != S){
            throw CMLException("data.size() != S:  ", data->size(), "!=", S);
        }   

        auto d = data->data().get();
        U u;
        for (size_t i = 0; i < S; ++i){
            read_U(f, u);
            *(d++) = u;
        }
    }

    template<typename T>
    tensor<T> read(std::istream& f){
        uint32_t magicNumber = read_u32(f);

        size_t numDims = ((magicNumber) & 0xff);
        std::vector<size_t> dims;
        dims.reserve(numDims);
        size_t S = 1;
        for (size_t i = 0; i < numDims; ++i){
            dims.emplace_back((size_t)read_u32(f));
            S *= dims[i];
        }

        tensor<T> data = cml::make_tensor<T>(dims);

        switch((magicNumber >> 8) & 0xff){
            case 0x08:
                read_t<T, uint8_t>(f, data, dims, S);
                break;
            case 0x09:
                read_t<T, int8_t>(f, data, dims, S);
                break;
            case 0x0B:
                read_t<T, short>(f, data, dims, S);
                break;
            case 0x0C:
                read_t<T, int>(f, data, dims, S);
                break;
            case 0x0D:
                read_t<T, float>(f, data, dims, S);
                break;
            case 0x0E:
                read_t<T, double>(f, data, dims, S);
                break;
            default:
                throw "Invalid data type";
        }

        return data;
    }

}

#endif // __CML_UTILS_DATAFORMATS_IDX_H__