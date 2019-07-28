#ifndef __CML_FUNCTIONS_TENSOROPS_TENSOROPS_H__
#define __CML_FUNCTIONS_TENSOROPS_TENSOROPS_H__


#include "../../Tensors/TensorTemplate.h"
#include "../../Tensors/Tensor2D.h"

namespace cml {


    /***********************************************************************************
    **************************** Tensor Multiplication *********************************
    ************************************************************************************/

    template<typename T>
    tensor<T> matmul(tensor2d<T> lhs, tensor2d<T> rhs);

    template<typename T>
    tensor<T> multiply(tensor<T> lhs, tensor<T> rhs);

    template <typename T>
    inline tensor<T> matmul(tensor<T> lhs, tensor<T> rhs) {
        return multiply(lhs, rhs);
    }

    template<typename T>
    inline tensor<T> operator*(tensor<T> lhs, tensor<T> rhs){
        return multiply(lhs, rhs);
    }


    /***********************************************************************************
    *************************** Tensor Inplace Division ********************************
    ************************************************************************************/

    template<typename T, typename U>
    inline tensor<T> inplaceDivision(tensor2d<T> t, const U& scalar);

    template<typename T, typename U>
    tensor<T> inplaceDivision(tensor<T> t, const U& scalar);

    template<typename T, typename U>
    inline tensor<T> operator/=(tensor<T> t, const U& scalar){
        return inplaceDivision(t, scalar);
    }



    /***********************************************************************************
    ******************************* Tensor Increment ***********************************
    ************************************************************************************/

    template<typename T>
    inline tensor<T> increment(tensor2d<T> lhs, tensor2d<T> rhs);

    template<typename T>
    tensor<T> increment(tensor<T> lhs, tensor<T> rhs);

    template<typename T>
    inline tensor<T> operator+=(tensor<T> lhs, tensor<T> rhs){ return increment(lhs, rhs); }



    /***********************************************************************************
    ******************************* Tensor Decrement ***********************************
    ************************************************************************************/

    template<typename T>
    inline tensor<T> decrement(tensor2d<T> lhs, tensor2d<T> rhs);

    template<typename T>
    tensor<T> decrement(tensor<T> lhs, tensor<T> rhs);

    template<typename T>
    inline tensor<T> operator-=(tensor<T> lhs, tensor<T> rhs){ return decrement(lhs, rhs); }

}

#endif // __CML_FUNCTIONS_TENSOROPS_TENSOROPS_H__
