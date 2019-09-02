#ifndef __CML_TENSORS_TENSORIMPL_H__
#define __CML_TENSORS_TENSORIMPL_H__

#include <algorithm>
#include <memory>
#include <ostream>

#include <Eigen/Core>
#include <unsupported/Eigen/CXX11/Tensor>

#include "Tensor.h"
#include "DCG.h"
#include "../Functions/TensorOps/TensorOps.h"
#include "../../Numeric/Numeric.h"

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
        S{(size_t)(m.size())},
        d{new T[S], std::default_delete<T[]>()} {

        if (S == 1){
            dims.emplace_back((size_t)(1));
        }
        else{
            dims.emplace_back((size_t)(m.rows()));
            dims.emplace_back((size_t)(m.cols()));
        }

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
        this->tensor<nDims>() = t;
    }

//     template<typename T> template<size_t... dims>
//     void Tensor<T>::initialize(){
//         this->dims = {dims...};
//         S = cml::numeric::product<dims...>();
//         d = std::shared_ptr<T>(new T[S], std::default_delete<T[]>());
//     }


    /******************************************************************
     ********************* make_tensor functions **********************
     ******************************************************************/

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
    // inline cml::tensor<T> Tensor<T>::make_tensor(Dims&&... dims){
    //     auto t = std::make_shared<Tensor<T>>();
    //     if (sizeof...(dims) > 0){
    //         t->dims = {(size_t)(dims)...};
    //         t->S = cml::numeric::product(t->dims);
    //         t->d = std::shared_ptr<T>(new T[t->S], std::default_delete<T[]>());
    //     }
    //     return t;
    // }
    // template<typename T, typename... Dims>
    // inline cml::tensor<T> make_tensor(Dims&&... dims){
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
    inline cml::tensor<T> make_tensor(nd_array<T, sizeof...(dims)+1> a, const bool& computeGrad){
        auto t = make_tensor<T, dim, dims...>(computeGrad);
        MultiDimensionalInitializerListProcessor<T, dim, dims...>::process(
            std::forward<nd_array<T, sizeof...(dims)+1>>(a), (T*)(t->data().get()));
        return t;
    }

    template <typename T>
    inline tensor<T> make_scalar(const T& t, const bool& computeGrad){
        auto u = make_tensor<T, 1>(computeGrad);
        u->item() = t;
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



    /******************************************************************
     ***************** Tensor Access Member functions *****************
     ******************************************************************/

    template<typename T>
    inline MatrixMap<T> Tensor<T>::matrix() {
        return Eigen::Map<DMatrix<T>>(d.get(), rows(), cols());
    }
    template<typename T> template<int nDims>
    Eigen::TensorMap<Eigen::Tensor<T, nDims>> Tensor<T>::tensor() {
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




    /******************************************************************
     ********************* Tensor Member Functions ********************
     ******************************************************************/


    template<typename T>
    inline cml::tensor<T> Tensor<T>::empty(const bool& computeGrad) {
        auto t = cml::make_tensor<T>(computeGrad);
        t->dims = dims;
        t->S = S;
        t->d = std::shared_ptr<T>(new T[S], std::default_delete<T[]>());
        return t;
    }
    template<typename T>
    inline cml::tensor<T> Tensor<T>::zeroLike(const bool& computeGrad) {
        auto t = cml::make_tensor<T>(computeGrad);
        t->dims = dims;
        t->S = S;
        t->d = std::shared_ptr<T>(new T[S](), std::default_delete<T[]>());
        return t;
    }
    template<typename T>
    inline cml::tensor<T> Tensor<T>::constant(const T& s, const bool& computeGrad) {
        if (s == 0){ return zeroLike(); }
        auto t = empty();
        t->fill(s);
        return t;
    }

    template<typename T>
    inline cml::tensor<T> Tensor<T>::abs() {
        return cml::abs(this->shared_from_this());
    }

    template<typename T>
    inline void Tensor<T>::apply(cml::UnaryFunction<T> f) {
        this->matrix() = this->matrix().unaryExpr(std::ptr_fun(f));
    }
    template<typename T>
    inline cml::tensor<T> Tensor<T>::expr(cml::UnaryFunction<T> f, const bool& computeGrad) {
        auto t = this->empty(computeGrad);
        t->matrix() = this->matrix().unaryExpr(std::ptr_fun(f));
        return t;
    }

    template<typename T>
    inline cml::tensor<T> Tensor<T>::matmul(cml::tensor<T> other){ return cml::matmul(this->shared_from_this(), other); }

    template<typename T>
    inline cml::tensor<T> Tensor<T>::mm(cml::tensor<T> other){ return cml::matmul(this->shared_from_this(), other); }

    template<typename T>
    inline cml::tensor<T> Tensor<T>::transpose(){ return cml::transpose(this->shared_from_this()); }

    /******************************************************************
     ********************* Other Tensor Functions *********************
     ******************************************************************/

    template<typename T>
    std::ostream& Tensor<T>::print(std::ostream& out){
        return cml::print(out, d.get(), d.get()+S);
    }

    template<typename T>
    std::ostream& operator<<(std::ostream& out, Tensor<T>* t){
        return out << t->matrix();
    }

}

#endif // __CML_TENSORS_TENSORIMPL_H__
