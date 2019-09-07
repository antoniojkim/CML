#ifndef __CML_FUNCTIONS_LINEAR_LINEAR_H__
#define __CML_FUNCTIONS_LINEAR_LINEAR_H__

#include "../../Tensors/Tensor.h"

namespace cml {
namespace Function {

    struct Linear {

        template<typename T>
        static tensor<T> forward(tensor<T> input, tensor<T> weights, tensor<T> bias = nullptr){
            tensor<T> t = nullptr;
            if (bias != nullptr){
                // It is faster to combine the add, matrix multiply and transpose operation
                t = addmatmulT(bias, input, weights);
            }
            else{
                // It is faster to combine the matrix multiply and transpose operation
                t = matmulT(input, weights);
            }

            return t;
        }
    };

    template<typename T>
    inline tensor<T> Linear(tensor<T> input, tensor<T> weights, tensor<T> bias = nullptr){
        return Linear::forward(input, weights, bias);
    }

};
};

#endif //__CML_FUNCTIONS_LINEAR_LINEAR_H__
