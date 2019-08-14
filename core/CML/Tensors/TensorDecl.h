#ifndef __CML_TENSORS_TENSORDECL_H__
#define __CML_TENSORS_TENSORDECL_H__

namespace cml {

    template <typename T> class TensorBase;
    template <typename T> class DCG;  // Dynamic Compute Graph

    /*
        Note that the lower case tensor is used for a shared_ptr to a Tensor object.
        Lowercase as it isn't a direct reference, but rather an indirect one.
    */
    template <typename T>
    using tensor = std::shared_ptr<TensorBase<T>>;
    template <typename T>
    using _tensor_ = TensorBase<T>*;


    template <typename T>
    using GradientFunction = std::vector<tensor<T>>(*)(std::vector<_tensor_<T>>&,
                                                       std::vector<tensor<T>>);


    template <typename T, int nDims> class Tensor;

    template <typename T, int nDims>
    using ntensor = std::shared_ptr<Tensor<T, nDims>>;

    #ifndef CAST_EIGEN_TENSOR
    #define CAST_EIGEN_TENSOR static_cast<Eigen::Tensor<T, nDims>>
    #endif // CAST_EIGEN_TENSOR

    #ifndef CAST_TENSOR_NDIMS
    #define CAST_TENSOR_NDIMS static_cast<cml::Tensor<T, nDims>*>
    #endif // CAST_TENSOR_NDIMS


    template <typename T>
    inline tensor<T> make_scalar(const T& t, const bool& computeGrad = false);
    
    template<typename T>
    tensor<T> make_tensor(const int& d1, const bool& computeGrad = false);
    template<typename T>
    tensor<T> make_tensor(const int& d1, const int& d2, const bool& computeGrad = false);
    template<typename T>
    tensor<T> make_tensor(const int& d1, const int& d2, const int& d3, const bool& computeGrad = false);
    template<typename T>
    tensor<T> make_tensor(const int& d1, const int& d2, const int& d3, const int& d4, const bool& computeGrad = false);
}

#endif // __CML_TENSORS_TENSORDECL_H__
