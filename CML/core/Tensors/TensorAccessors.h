#ifndef __TENSOR_ACCESSORS_H__
#define __TENSOR_ACCESSORS_H__

#include <algorithm>
#include <memory>

#include <Eigen/Core>
#include <unsupported/Eigen/CXX11/Tensor>

#include "Tensor.h"

namespace cml {

    template<typename T>
    inline MatrixMap<T> Tensor<T>::matrix() {
        return Eigen::Map<DMatrix<T>>(d.get(), rows(), cols());
    }
    template<typename T> template<int nDims>
    Eigen::TensorMap<Eigen::Tensor<T, nDims>> Tensor<T>::toTensor() {
        if (int(nDims) != dims.size()){
            throw InvalidDimensionException("template nDims (", nDims, ") does not match object's dim size (", dims.size(), ")");
        }

        std::array<int, nDims> arr;
        std::copy_n(dims.begin(), nDims, arr.begin());

        return Eigen::TensorMap<Eigen::Tensor<T, nDims>>(d.get(), arr);
    }

    template<typename T>
    T& Tensor<T>::at(std::initializer_list<size_t> dims){
        if (numDims != this->dims.size()){
            throw CMLException("Tensor::at:  Invalid Indices: ", dims, "  Dims: ", this->dims);
        }

        size_t index = 0, j = 0;
        size_t s = S;
        for (const auto& d : dims){
            const auto m = this->dims[j++];
            if (d > m){
                throw CMLException("Tensor::at:  Index out of bounds.  Got: ", dims, "  Dims:", this->dims);
            }
            s /= m;
            index += d * s;
        }

        if (index >= S){
            throw CMLException("Tensor::at:  Invalid Indices: ", dims, "  Dims: ", this->dims);
        }

        return this->d.get()[index];
    }

    template<typename T> template<typename... Dims>
    T& Tensor<T>::at(const Dims&... dims){
        constexpr size_t numDims = sizeof...(Dims);
        if (numDims != this->dims.size()){
            throw CMLException("Tensor::at:  Invalid Indices: ", std::vector<size_t>({(size_t)(dims)...}), "  Dims: ", this->dims);
        }

        size_t index = 0, j = 0;
        size_t s = S;
        for (const auto& d : {dims...}){
            const auto& m = this->dims[j++];
            if (d >= m){
                throw CMLException("Tensor::at:  Index out of bounds. ", d, ">=", m, "   Got: ", std::vector<size_t>({(size_t)(dims)...}), "  Dims:", this->dims);
            }
            s /= m;
            index += d * s;
        }

        if (index >= S){
            throw CMLException("Tensor::at:  ", index, ">=", S, "  Invalid Indices: ", std::vector<size_t>({(size_t)(dims)...}), "  Dims: ", this->dims);
        }

        return this->d.get()[index];
    }


}

#endif  // __TENSOR_ACCESSORS_H__
