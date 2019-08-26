#ifndef __CML_TENSORS_TENSORIMPL_H__
#define __CML_TENSORS_TENSORIMPL_H__

#include <algorithm>
#include <ostream>

#include <Eigen/Core>
#include <unsupported/Eigen/CXX11/Tensor>

#include "Tensor.h"
#include "../Functions/TensorOps/TensorOps.h"
#include "../../Numeric/Numeric.h"

namespace cml {

    /******************************************************************
     ************************* Constructors ***************************
     ******************************************************************/
    
    template<typename T>
    Tensor<T>::Tensor(const bool& computeGrad):
        computeGrad(computeGrad) {}
    
    template<typename T>
    Tensor<T>::Tensor(const std::vector<size_t>& dims, const bool& computeGrad):  
        computeGrad(computeGrad),
        dims{std::begin(dims), std::end(dims)},
        S{cml::numeric::product(dims)},
        d{new T[S], std::default_delete<T[]>()} {}
    
    template<typename T>
    Tensor<T>::Tensor(std::initializer_list<size_t> dims, const bool& computeGrad):  
        computeGrad(computeGrad),
        dims{std::begin(dims), std::end(dims)},
        S{cml::numeric::product(dims)},
        d{new T[S], std::default_delete<T[]>()} {}

    template<typename T>
    Tensor<T>::Tensor(const DMatrix<T>& m, const bool& computeGrad): 
        computeGrad{computeGrad},
        S{(size_t)(m.size())},
        dims{{m.rows(), m.cols()}},
        d{std::make_shared<T[]>(new T[S], std::default_delete<T[]>())} {

        T* data = d.get();
        T* m_data = m.data();

        // TODO: Possibly think about adding support for both row major and column major eigen matrices
        std::copy(m_data, m_data+S, data);
    }
    template<typename T> template<int nDims>
    Tensor<T>::Tensor(const Eigen::Tensor<T, nDims>& t, const bool& computeGrad): 
        computeGrad{computeGrad},
        S{(size_t)(t.size())},
        dims{std::begin(t.dimensions()), std::end(t.dimensions())},
        d{std::make_shared<T[]>(new T[S], std::default_delete<T[]>())} {

        T* data = d.get();
        T* t_data = t.data();

        // TODO: Possibly think about adding support for both row major and column major eigen tensors
        std::copy(t_data, t_data+S, data);
    }

    template<typename T> template<size_t... dims>
    void Tensor<T>::initialize(){
        this->dims = {dims...};
        S = cml::numeric::product<dims...>();
        d = std::make_shared<T[]>(new T[S], std::default_delete<T[]>());
    }


    /******************************************************************
     ********************* make_tensor functions **********************
     ******************************************************************/

    template <typename T>
    inline tensor<T> make_scalar(const T& t, const bool& computeGrad){
        auto u = std::make_shared<Tensor<T>>({1}, computeGrad);
        u->item() = t;
        return u;
    }
    
    template<typename T>
    inline tensor<T> make_tensor(std::vector<size_t> dims, const bool& computeGrad){
        return std::make_shared<Tensor<T>>(std::forward<std::vector<size_t>>(dims), computeGrad);
    }
    template<typename T>
    inline tensor<T> make_tensor(std::initializer_list<size_t> dims, const bool& computeGrad){
        return std::make_shared<Tensor<T>>(std::forward<std::initializer_list<size_t>>(dims), computeGrad);
    }
    template<typename T, size_t... dims>
    inline tensor<T> make_tensor(const bool& computeGrad){
        auto t = std::make_shared<Tensor<T>>(computeGrad);
        throw UnimplementedException("make_tensor with variadic templates");
//         t->initialize<dims...>();
        return t;
    }

    template<typename T>
    inline tensor<T> make_tensor(const DMatrix<T>& m, const bool& computeGrad){
        return std::make_shared<Tensor<T>>(m, computeGrad);
    }
    template<typename T, int nDims>
    inline tensor<T> make_tensor(const Eigen::Tensor<T, nDims>& t, const bool& computeGrad){
        return std::make_shared<Tensor<T>>(t, computeGrad);
    }



    /******************************************************************
     ***************** Tensor Access Member functions *****************
     ******************************************************************/
    
    template<typename T>
    MatrixMap<T> Tensor<T>::matrix() {
        int R, C;
        R = dims[0];
        switch(dims.size()){
            case 2:
                C = dims[1];
                break;
            default:
                C = S / R;
                break;
        }
        return Eigen::Map<DMatrix<T>>(d.get(), R, C);
    }
    template<typename T> template<int nDims>
    Eigen::TensorMap<Eigen::Tensor<T, nDims>> Tensor<T>::tensor() {
        if (int(nDims) != dims.size()){
            std::ostringstream message;
            message << "template nDims (" << nDims << ") does not match object's dim size (" << dims.size() << ")";
            throw InvalidDimensionException(message);
        }

        std::array<int, nDims> arr;
        std::copy_n(dims.begin(), nDims, arr.begin());

        return Eigen::TensorMap<Eigen::Tensor<T, nDims>>(d.get(), arr);
    }
    
    template<typename T>
    T& Tensor<T>::at(std::initializer_list<int> dims){
        if (dims.size() >= this->dims.size()){
            throw CMLException("Tensor::at:  Too many dims: ", dims.size());
        }

        int index = 0, j = 0;
        for (auto& d : dims){
            index += d * this->dims[j++];
        }

        if (index >= S){
            throw CMLException("Tensor::at:  Invalid Indices: ", dims);
        }

        return this->d[index];
    }
    
    template<typename T> template<typename... Dim>
    T& Tensor<T>::at(Dim&&... dims){
        if (sizeof...(dims) >= this->dims.size()){
            throw CMLException("Tensor::at:  Too many dims: ", sizeof...(dims));
        }

        int index = 0, j = 0;
        for (auto& d : {dims...}){
            index += d * this->dims[j++];
        }

        if (index >= S){
            throw CMLException("Tensor::at:  Invalid Indices: ", std::vector<size_t>({dims...}));
        }

        return this->d[index];
    }
    
    


    /******************************************************************
     **************** Tensor Modifier Member functions ****************
     ******************************************************************/

    template<typename T>
    inline void Tensor<T>::fill(const T& coefficient){
        std::fill_n(d.get(), S, coefficient);
    }
    template<typename T>
    inline void Tensor<T>::ones(){
        std::fill_n(d.get(), S, 1);
    }
    template<typename T>
    inline void Tensor<T>::zero(){
        std::fill_n(d.get(), S, 0);
    }

    template<typename T>
    void Tensor<T>::randomize(cml::Random::Function<T> r){
        std::transform(d, d+S, d, r);
    }
    

    


    /******************************************************************
     ********************* Other Tensor Functions *********************
     ******************************************************************/
    
    template<typename T>
    std::ostream& operator<<(std::ostream& out, Tensor<T>* t){
        return out << t->matrix();
    }

}

#endif // __CML_TENSORS_TENSORIMPL_H__
