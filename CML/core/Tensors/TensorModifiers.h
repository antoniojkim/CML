#ifndef __TENSOR_MODIFIERS_H__
#define __TENSOR_MODIFIERS_H__


#include <memory>

#include <Eigen/Core>
#include <unsupported/Eigen/CXX11/Tensor>

#include "Tensor.h"
#include "../../Numeric/Numeric.h"

namespace cml {

    /******************************************************************
     **************** Tensor Modifier Member functions ****************
     ******************************************************************/

    template<typename T> template<size_t... Dims>
    void Tensor<T>::set(nd_array<T, sizeof...(Dims)> a){
        if (cml::numeric::product<Dims...>() > S){
            throw CMLException("Initializer list ", std::vector<size_t>({Dims...}), " has dimensions that exceed current tensor: ", this->dims);
        }
        MultiDimensionalInitializerListProcessor<T, Dims...>::process(std::forward<nd_array<T, sizeof...(Dims)>>(a),
                                                                      (T*)(d.get()));
    }

    template<typename T>
    inline void Tensor<T>::fill(const T& scalar){
        this->matrix().fill(scalar);
    }
    template<typename T>
    inline void Tensor<T>::ones(){
        this->matrix().setOnes();
    }
    template<typename T>
    inline void Tensor<T>::zero(){
        this->matrix().setZero();
    }

    template<typename T>
    void Tensor<T>::randomize(cml::Random::Function<T> r){
        std::transform(d.get(), d.get()+S, d.get(), r);
    }


#endif // __TENSOR_MODIFIERS_H__
