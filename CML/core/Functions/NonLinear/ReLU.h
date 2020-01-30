#ifndef __CML_FUNCTIONS_NONLINEAR_RELU_H__
#define __CML_FUNCTIONS_NONLINEAR_RELU_H__

#include <functional>

#include "NonLinear.h"
#include "../../Tensors/Tensor.h"


namespace cml {
namespace Function {

    template<typename T>
    inline tensor<T> ReLU(tensor<T> input){
        return input->abs();
    }

};
};

#endif // __CML_FUNCTIONS_NONLINEAR_H__
