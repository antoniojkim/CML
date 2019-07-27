#ifndef __CML_NN_LOSS_CRITERION_H__
#define __CML_NN_LOSS_CRITERION_H__

#include "../../Tensors/Tensor2D.h"

namespace cml {
namespace nn {


    template<typename T = float>
    struct Criterion {
        virtual cml::tensor<T> forward(cml::tensor<T> actual, cml::tensor<T> expected) = 0;
        inline cml::tensor<T> operator()(cml::tensor<T> actual, cml::tensor<T> expected){
            return forward(actual, expected);
        }
    };
    

}
}

#endif // __CML_NN_LOSS_CRITERION_H__