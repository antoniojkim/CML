#ifndef __MAKE_TENSOR_H__
#define __MAKE_TENSOR_H__


#include <memory>

#include <Eigen/Core>
#include <unsupported/Eigen/CXX11/Tensor>

#include "../Tensor.h"
#include "../../../numeric/Numeric.h"

namespace cml {

    template<typename T>
    inline tensor<T> Tensor<T>::make_tensor(const bool& computeGrad){
        return std::shared_ptr<Tensor<T>>(new Tensor<T>(computeGrad));
    }
    template<typename T>
    inline tensor<T> make_tensor(const bool& computeGrad){ return Tensor<T>::make_tensor(computeGrad); }

    template<typename T>
    inline tensor<T> Tensor<T>::make_tensor(const std::vector<size_t>& dims, const bool& computeGrad){
        return std::shared_ptr<Tensor<T>>(new Tensor<T>(dims, computeGrad));
    }
    template<typename T>
    inline tensor<T> make_tensor(const std::vector<size_t>& dims, const bool& computeGrad){
        return Tensor<T>::make_tensor(dims, computeGrad);
    }

    // template<typename T> template<typename... Dims>
    // inline tensor<T> Tensor<T>::make_tensor(Dims&&... dims){
    //     auto t = std::make_shared<Tensor<T>>();
    //     if (sizeof...(dims) > 0){
    //         t->dims = {(size_t)(dims)...};
    //         t->S = cml::numeric::product(t->dims);
    //         t->d = std::shared_ptr<T>(new T[t->S], std::default_delete<T[]>());
    //     }
    //     return t;
    // }
    // template<typename T, typename... Dims>
    // inline tensor<T> make_tensor(Dims&&... dims){
    //     return Tensor<T>::template make_tensor<Dims...>(std::forward<Dims>(dims)...);
    // }

    template<typename T> template<size_t dim, size_t... dims>
    inline tensor<T> Tensor<T>::make_tensor(const bool& computeGrad){
        auto t = std::shared_ptr<Tensor<T>>(new Tensor<T>(computeGrad));
        t->dims = {dim, (size_t)(dims)...};
#ifdef DEBUG
        if (t->dims.size() != (sizeof...(dims))+1) throw CMLException("Incorrect behaviour");
#endif
        constexpr size_t P = cml::numeric::product<dim, dims...>();
        t->S = P;
        t->d = std::shared_ptr<T>(new T[P], std::default_delete<T[]>());
        return t;
    }
    template<typename T, size_t dim, size_t... dims>
    inline tensor<T> make_tensor(const bool& computeGrad){
        return Tensor<T>::template make_tensor<dim, dims...>(computeGrad);
    }

    template<typename T, size_t dim, size_t... dims>
    inline tensor<T> make_tensor(nd_array<T, sizeof...(dims)+1> a, const bool& computeGrad){
        auto t = make_tensor<T, dim, dims...>(computeGrad);
        MultiDimensionalInitializerListProcessor<T, dim, dims...>::process(
            std::forward<nd_array<T, sizeof...(dims)+1>>(a), (T*)(t->data().get()));
        return t;
    }
    template<typename T, size_t dim, size_t... dims>
    tensor<T> make_tensor(const DMatrix<T>& m, const bool& computeGrad){
        auto t = make_tensor<T, dim, dims...>(computeGrad);
        if (t->size() != m.size()){
            throw CMLException("Tensor size does not match matrix size: ", t->size(), " != ", m.size());
        }
        t->matrix() = m;
        return t;
    }

    template <typename T>
    inline tensor<T> make_scalar(const T& t, const bool& computeGrad){
        auto u = make_tensor<T, 1>(computeGrad);
        u->item() = t;
        return u;
    }
    template <typename T>
    tensor<T> make_scalar(const DMatrix<T>& m, const bool& computeGrad){
        if (m.rows() != 1 || m.cols() != 1){
            throw CMLException("make_scalar:  dmatrix is not scalar: [", m.rows(), ", ", m.cols(), "]");
        }
        auto u = make_tensor<T, 1>(computeGrad);
        u->item() = m(0, 0);
        return u;
    }

    template<typename T>
    inline tensor<T> Tensor<T>::make_tensor(const DMatrix<T>& m, const bool& computeGrad){
        return std::shared_ptr<Tensor<T>>(new Tensor<T>(m, computeGrad));
    }
    template<typename T>
    inline tensor<T> make_tensor(const DMatrix<T>& m, const bool& computeGrad){
        return Tensor<T>::make_tensor(m, computeGrad);
    }

    template<typename T> template<int nDims>
    inline tensor<T> Tensor<T>::make_tensor(const Eigen::Tensor<T, nDims>& t, const bool& computeGrad){
        return std::shared_ptr<Tensor<T>>(new Tensor<T>(t, computeGrad));
    }
    template<typename T, int nDims>
    inline tensor<T> make_tensor(const Eigen::Tensor<T, nDims>& t, const bool& computeGrad){
        return Tensor<T>::template make_tensor<nDims>(t, computeGrad);
    }

}

#endif  // __MAKE_TENSOR_H__
