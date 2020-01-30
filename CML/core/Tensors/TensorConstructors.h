#ifndef __TENSOR_CONSTRUCTORS_H__
#define __TENSOR_CONSTRUCTORS_H__

#include <memory>

#include <Eigen/Core>
#include <unsupported/Eigen/CXX11/Tensor>

#include "Tensor.h"

namespace cml {

    /******************************************************************
     ************************* Constructors ***************************
     ******************************************************************/

    template<typename T>
    Tensor<T>::Tensor(const bool& computeGrad): computeGrad{computeGrad} {}

    template<typename T>
    Tensor<T>::Tensor(const std::vector<size_t>& dims, const bool& computeGrad):
        computeGrad(computeGrad),
        dims{std::begin(dims), std::end(dims)},
        S{cml::numeric::product(dims)},
        d{new T[S], std::default_delete<T[]>()} {}

    // template<typename T>
    // Tensor<T>::Tensor(std::initializer_list<size_t> dims, const bool& computeGrad):
    //     computeGrad(computeGrad),
    //     dims{std::begin(dims), std::end(dims)},
    //     S{cml::numeric::product(dims)},
    //     d{new T[S], std::default_delete<T[]>()} {}

    template<typename T>
    Tensor<T>::Tensor(const DMatrix<T>& m, const bool& computeGrad):
        computeGrad{computeGrad},
        dims{{(size_t)(m.rows()), (size_t)(m.cols())}},
        S{(size_t)(m.size())},
        d{new T[S], std::default_delete<T[]>()} {

        // TODO: Possibly think about adding support for both row major and column major eigen matrices
        this->matrix() = m;
    }
    template<typename T> template<int nDims>
    Tensor<T>::Tensor(const Eigen::Tensor<T, nDims>& t, const bool& computeGrad):
        computeGrad{computeGrad},
        dims{std::begin(t.dimensions()), std::end(t.dimensions())},
        S{(size_t)(t.size())},
        d{new T[S], std::default_delete<T[]>()} {

        // TODO: Possibly think about adding support for both row major and column major eigen tensors
        this->toTensor<nDims>() = t;
    }

//     template<typename T> template<size_t... dims>
//     void Tensor<T>::initialize(){
//         this->dims = {dims...};
//         S = cml::numeric::product<dims...>();
//         d = std::shared_ptr<T>(new T[S], std::default_delete<T[]>());
//     }

}

#endif  // __TENSOR_CONSTRUCTORS_H__
