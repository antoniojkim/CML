#ifndef __CML_FUNCTIONS_TENSOROPS_TENSOR_SCALAR_MULTIPLICATION_H__
#define __CML_FUNCTIONS_TENSOROPS_TENSOR_SCALAR_MULTIPLICATION_H__

#include "TensorOps.h"

namespace cml {

    template<typename T, typename U>
    tensor<T> multiply(tensor<T> t, const U& scalar){
        auto u = t->empty(t->computeGrad);
        u->matrix() = t->matrix() * (T)(scalar);

        if (u->computeGrad){
            u->initGraph({t}, [scalar](std::vector<tensor<T>>& params, std::vector<tensor<T>> output) -> std::vector<tensor<T>> {
#ifdef DEBUG
                using namespace std;
                cout << "Tensor Scalar Multiplication Backward" << endl;
#endif
                tensor<T> t_grad = make_scalar<T>((T)(scalar));

                return {t_grad};
            });
        }

        return t;
    }

}

#endif // __CML_FUNCTIONS_TENSOROPS_TENSOR_SCALAR_MULTIPLICATION_H__
