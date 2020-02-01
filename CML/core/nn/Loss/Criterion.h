#ifndef __CML_NN_LOSS_CRITERION_H__
#define __CML_NN_LOSS_CRITERION_H__

#include "../../Tensor.h"

namespace cml {
namespace nn {


    template<typename T = float>
    struct Criterion {
        virtual tensor<T> forward(tensor<T> actual, tensor<T> expected) = 0;
        inline tensor<T> operator()(tensor<T> actual, tensor<T> expected){
            return forward(actual, expected);
        }
    };


}
}

#endif // __CML_NN_LOSS_CRITERION_H__