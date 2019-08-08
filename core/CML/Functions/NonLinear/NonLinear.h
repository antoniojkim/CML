#ifndef __CML_FUNCTIONS_NONLINEAR_NONLINEAR_H__
#define __CML_FUNCTIONS_NONLINEAR_NONLINEAR_H__

#include "../../Tensors/TensorDecl.h"

namespace cml {

    template<typename T, int nDims> class Tensor;

    namespace Function {

        template<typename T>
        tensor<T> ReLU(tensor<T> input);

        template<typename T>
        tensor<T> Sigmoid(tensor<T> input);

        template<typename T>
        tensor<T> Tanh(tensor<T> input);

        template<typename T, int nDims>
        tensor<T> Softmax(Tensor<T, nDims>* input);
        template<typename T>
        tensor<T> Softmax(tensor<T> input);

    }
}

#endif // __CML_FUNCTIONS_NONLINEAR_NONLINEAR_H__
