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
                // It is faster to combine the add and multiply operation
                t = addmatmul(bias, input, weights->transpose());
            }
            else{
                t = input * weights->transpose();
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
