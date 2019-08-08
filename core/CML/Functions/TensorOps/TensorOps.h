#ifndef __CML_FUNCTIONS_TENSOROPS_TENSOROPS_H__
#define __CML_FUNCTIONS_TENSOROPS_TENSOROPS_H__

#include "../../Tensors/TensorDecl.h"

namespace cml {

    /***********************************************************************************
    **************************** Tensor Multiplication *********************************
    ************************************************************************************/

    template<typename T>
    tensor<T> transpose(TensorBase<T>* t);
    
    template<typename T>
    inline tensor<T> transpose(tensor<T> t){
        return transpose(t.get());
    }

    /***********************************************************************************
    **************************** Tensor Multiplication *********************************
    ************************************************************************************/

    template<typename T>
    tensor<T> matmul(TensorBase<T>* lhs, TensorBase<T>* rhs);
    
    template<typename T>
    inline tensor<T> matmul(tensor<T> lhs, tensor<T> rhs){
        return matmul(lhs.get(), rhs.get());
    }

    // TODO:  Replace this with more general function, i.e. Eigen::Tensor Contractions
    template<typename T>
    inline tensor<T> operator*(tensor<T> lhs, tensor<T> rhs){
        return matmul(lhs.get(), rhs.get());
    }

    /***********************************************************************************
    ***************************** Tensor Add Multiply **********************************
    ************************************************************************************/

    template<typename T>
    tensor<T> addmatmul(tensor<T> t1, tensor<T> t2, tensor<T> t3);

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

}

#endif // __CML_FUNCTIONS_TENSOROPS_TENSOROPS_H__
