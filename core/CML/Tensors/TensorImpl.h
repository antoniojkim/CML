#ifndef __CML_TENSORS_TENSORIMPL_H__
#define __CML_TENSORS_TENSORIMPL_H__

#include <ostream>

#include <Eigen/Core>
#include <unsupported/Eigen/CXX11/Tensor>

#include "Tensor.h"
#include "../../Numeric/Numeric.h"
#include "../Functions/TensorOps/TensorOps.h"

namespace cml {


    template<size_t... dims>
    void initialize(){
        this->dims = {dims...};
        S = cml::product<dims...>();
    }

    template<typename T>
    MatrixMap<T> Tensor<T>::matrix() {
        int R, C;
        R = dims[0];
        switch(dims.size()){
            case 2:
                C = dims[1];
                break;
            default;
                C = s / R;
                break;
        }
        return Eigen::Map<DMatrix<T>>(d, R, C);
    }
    template<typename T> template<int nDims>
    Eigen::TensorMap<Eigen::Tensor<T, nDims>> Tensor<T>::tensor() {
        if (int(nDims) != dims.size()){
            std::ostringstream message;
            message << "template nDims (" << nDims << ") does not match object's dim size (" << dims.size() << ")";
            throw InvalidDimensionException(message);
        }

        std::array<int, nDims> arr;
        std::copy_n(v1.begin(), nDims, arr.begin());

        return Eigen::TensorMap<Eigen::Tensor<T, nDims>>(d, arr);
    }
    
    template<typename T>
    T& Tensor<T>::at(std::initializer_list<int> dims){
        if (dims.size() >= this->dims.size()){
            CML_THROW("Tensor::at:  Too many dims: " << dims.size());
        }

        int index = 0, j = 0;
        for (auto& d : dims){
            index += d * this->dims[j++];
        }

        if (index >= S){
            CML_THROW("Tensor::at:  Invalid Indices: " << dims);
        }

        return this->d[index];
    }

}

#endif // __CML_TENSORS_TENSORIMPL_H__
