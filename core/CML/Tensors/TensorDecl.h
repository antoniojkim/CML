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
    using GradientFunction = std::vector<tensor<T>(*)(std::vector<_tensor_<T>>&,
                                                      std::vector<tensor<T>>)>;

}

#endif // __CML_TENSORS_TENSORDECL_H__
