#ifndef __CML_TENSORS_TENSORDECL_H__
#define __CML_TENSORS_TENSORDECL_H__

#include <initializer_list>

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
}

#endif // __CML_TENSORS_TENSORDECL_H__
