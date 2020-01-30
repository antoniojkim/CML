#ifndef __CML_FUNCTIONS_TENSOROPS_TENSOROPS_H__
#define __CML_FUNCTIONS_TENSOROPS_TENSOROPS_H__

#include "../../Tensors/TensorDecl.h"

namespace cml {

    /***********************************************************************************
    ****************************** Tensor Transpose ************************************
    ************************************************************************************/

    template<typename T>
    inline tensor<T> transpose(tensor<T> t);

    /***********************************************************************************
    ************************* Tensor Scalar Multiplication *****************************
    ************************************************************************************/

    template<typename T, typename U>
    tensor<T> multiply(tensor<T> t, const U& scalar);

    template<typename T, typename U>
    inline tensor<T> operator*(tensor<T> t, const U& scalar){ return multiply(t, scalar); }

    template<typename T, typename U>
    inline tensor<T> operator*(const U& scalar, tensor<T> t){ return multiply(t, scalar); }

    /***********************************************************************************
    **************************** Tensor Multiplication *********************************
    ************************************************************************************/

    template<typename T>
    tensor<T> matmul(tensor<T> lhs, tensor<T> rhs);

    // TODO:  Replace this with more general function, i.e. Eigen::Tensor Contractions
    template<typename T>
    inline tensor<T> operator*(tensor<T> lhs, tensor<T> rhs){
        return multiply(lhs, rhs);
    }

    /***********************************************************************************
    ***************************** Tensor Add Multiply **********************************
    ************************************************************************************/

    template<typename T>
    tensor<T> addmatmul(tensor<T> t1, tensor<T> t2, tensor<T> t3);

    template<typename T>
    tensor<T> addmatmulT(tensor<T> t1, tensor<T> t2, tensor<T> t3);

    template<typename T>
    tensor<T> addMultiply(tensor<T> t1, tensor<T> t2, tensor<T> t3);



    /***********************************************************************************
    *************************** Tensor Inplace Division ********************************
    ************************************************************************************/

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
    tensor<T> increment(tensor<T> lhs, tensor<T> rhs);

    template<typename T>
    inline tensor<T> operator+=(tensor<T> lhs, tensor<T> rhs){ return increment(lhs, rhs); }



    /***********************************************************************************
    ******************************* Tensor Decrement ***********************************
    ************************************************************************************/

    template<typename T>
    tensor<T> decrement(tensor<T> lhs, tensor<T> rhs);

    template<typename T>
    inline tensor<T> operator-=(tensor<T> lhs, tensor<T> rhs){ return decrement(lhs, rhs); }



    /***********************************************************************************
    ******************** Tensor Coefficient-wise Absolute Value ************************
    ************************************************************************************/

    template<typename T>
    tensor<T> abs(tensor<T> input);

}

#endif // __CML_FUNCTIONS_TENSOROPS_TENSOROPS_H__
