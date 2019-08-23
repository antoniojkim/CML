#ifndef __CML_FUNCTIONS_TENSOROPS_TENSOR_SCALAR_MULTIPLICATION_H__
#define __CML_FUNCTIONS_TENSOROPS_TENSOR_SCALAR_MULTIPLICATION_H__

#include "TensorOps.h"

namespace cml {

    template<typename T, int nDims>
    tensor<T> multiply(tensor<T> t, const T& scalar){
        auto u = make_tensor<T>(CAST_TENSOR(
            t->tensor() * scalar;
        ), t->computeGrad);

        if (t->computeGrad){
            t->initGraph({t}, [scalar](std::vector<tensor<T>>& params, std::vector<tensor<T>> output) -> std::vector<tensor<T>> {
#ifdef DEBUG
                using namespace std;
                cout << "Tensor Scalar Multiplication Backward" << endl;
#endif
                tensor<T> t_grad = make_scalar<T>(scalar);

                return {t_grad};
            });
        }

        return t;
    }

    template<typename T, int nDims>
    inline tensor<T> operator*(tensor<T> t, const T& scalar){ return multiply(t, scalar); }

    template<typename T, int nDims>
    inline tensor<T> operator*(const T& scalar, tensor<T> t){ return multiply(t, scalar); }

    template<typename T>
    inline tensor<T> operator*(tensor<T> t, const T& scalar){ return t->multiply(scalar); }

    template<typename T>
    inline tensor<T> operator*(const T& scalar, tensor<T> t){ return t->multiply(scalar); }

}

#endif // __CML_FUNCTIONS_TENSOROPS_TENSOR_SCALAR_MULTIPLICATION_H__
