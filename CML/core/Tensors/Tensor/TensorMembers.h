#ifndef __TENSOR_MEMBERS_H__
#define __TENSOR_MEMBERS_H__

#include <memory>

#include "../Tensor.h"
#include "../../Functions/TensorOps/TensorOps.h"

/******************************************************************
 ********************* Tensor Member Functions ********************
 ******************************************************************/

// template<typename T>
// tensor<T> Tensor<T>::concat(tensor<T> other, const unsigned int& axis){
    
// }

template<typename T>
inline tensor<T> Tensor<T>::empty(const bool& computeGrad) {
    auto t = make_tensor<T>(computeGrad);
    t->dims = dims;
    t->S = S;
    t->d = std::shared_ptr<T>(new T[S], std::default_delete<T[]>());
    return t;
}

template<typename T>
inline tensor<T> Tensor<T>::zeroLike(const bool& computeGrad) {
    auto t = make_tensor<T>(computeGrad);
    t->dims = dims;
    t->S = S;
    t->d = std::shared_ptr<T>(new T[S](), std::default_delete<T[]>());
    return t;
}
template<typename T>
inline tensor<T> Tensor<T>::constant(const T& s, const bool& computeGrad) {
    if (s == 0){ return zeroLike(); }
    auto t = empty();
    t->fill(s);
    return t;
}

template<typename T>
inline tensor<T> Tensor<T>::abs() {
    return abs(this->shared_from_this());
}

template<typename T>
inline void Tensor<T>::apply(UnaryFunction<T> f) {
    this->matrix() = this->matrix().unaryExpr(std::ptr_fun(f));
}
template<typename T>
inline tensor<T> Tensor<T>::expr(UnaryFunction<T> f, const bool& computeGrad) {
    auto t = this->empty(computeGrad);
    t->matrix() = this->matrix().unaryExpr(std::ptr_fun(f));
    return t;
}

template<typename T>
inline tensor<T> Tensor<T>::matmul(tensor<T> other){ return matmul(this->shared_from_this(), other); }

template<typename T>
inline tensor<T> Tensor<T>::mm(tensor<T> other){ return matmul(this->shared_from_this(), other); }

template<typename T>
inline tensor<T> Tensor<T>::transpose(){ return transpose(this->shared_from_this()); }

#endif // __TENSOR_MEMBERS_H__