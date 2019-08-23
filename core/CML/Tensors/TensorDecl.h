#ifndef __CML_TENSORS_TENSORDECL_H__
#define __CML_TENSORS_TENSORDECL_H__

#include <initializer_list>

#include <Eigen/Core>
#include <unsupported/Eigen/CXX11/Tensor>

namespace cml {

    template <typename T> class Tensor;
    template <typename T> class DCG;  // Dynamic Compute Graph

    /*
        Note that the lower case tensor is used for a shared_ptr to a Tensor object.
        Lowercase as it isn't a direct reference, but rather an indirect one.
    */
    template <typename T>
    using tensor = std::shared_ptr<Tensor<T>>;


    template <typename T>
    using GradientFunction = std::vector<tensor<T>>(*)(std::vector<tensor<T>>&,
                                                       std::vector<tensor<T>>);

    #ifndef CAST_MATRIX
    #define CAST_MATRIX static_cast<DMatrix<T>>
    #endif // CAST_EIGEN_TENSOR

    #ifndef CAST_TENSOR
    #define CAST_TENSOR static_cast<Eigen::Tensor<T, nDims>>
    #endif // CAST_TENSOR


    template <typename T>
    inline tensor<T> make_scalar(const T& t, const bool& computeGrad = false);
    
    template<typename T>
    tensor<T> make_tensor(std::initializer_list<int> d1, const bool& computeGrad = false);
    

    template <typename T>
    using DMatrix = Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>;  // Dynamic Matrix
    template <typename T>
    using RefMatrix = Eigen::Ref<DMatrix<T>>;  // Ref to Dynamic Matrix
    template <typename T>
    using DBlock = Eigen::Block<DMatrix<T>, Eigen::Dynamic, Eigen::Dynamic, false>;  // Dynamic Block
    template <typename T>
    using DArray = Eigen::Array<T, Eigen::Dynamic, Eigen::Dynamic>;  // Dynamic Array
    template<typename T>
    using MatrixMap = Eigen::Map<DMatrix<T>, 0, Eigen::Stride<0, 0> >;
}

#endif // __CML_TENSORS_TENSORDECL_H__
