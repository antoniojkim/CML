#ifndef __CML_TENSORS_TENSOROPS_H__
#define __CML_TENSORS_TENSOROPS_H__

#include "TensorTemplate.h"

namespace cml {

    template<typename T>
    tensor<T> multiply(tensor2d<T> lhs, tensor<T> rhs){
        switch(rhs->getType()){
            case TensorType::MATRIX:
                return lhs*std::static_pointer_cast<Tensor2D<T>>(rhs);
            default:
                throw UnsupportedOperationException("Multiplication between unsupported tensor types");
        }
    }

    template<typename T>
    tensor<T> multiply(tensor<T> lhs, tensor<T> rhs){
        switch(lhs->getType()){
            case TensorType::MATRIX:
                return multiply(std::static_pointer_cast<Tensor2D<T>>(lhs), rhs);
            default:
                throw UnsupportedOperationException("Multiplication between unsupported tensor types");
        }
    }

    template<typename T>
    inline tensor<T> operator*(tensor<T> lhs, tensor<T> rhs){
        return multiply(lhs, rhs);
    }

}

#endif // __CML_TENSORS_TENSOROPS_H__
