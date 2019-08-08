#ifndef __CML_FUNCTIONS_NONLINEAR_TANH_H__
#define __CML_FUNCTIONS_NONLINEAR_TANH_H__

#include <cmath>

#include "NonLinear.h"
#include "../../Tensors/Tensor.h"


namespace cml {
namespace Function {
    
    struct Tanh {

        template<typename T>
        static T gradient(const T& x){
            auto coshx = cosh(x);
            return (T)(1.0 / coshx*coshx);
        }

        template<typename T>
        static std::vector<tensor<T>> backward(std::vector<_tensor_<T>>& params, std::vector<tensor<T>> output) {
            tensor<T> output_grad = output.at(0);
            tensor<T> input_grad = output_grad->expr(&gradient);
            return {input_grad};
        }
        
        template<typename T>
        static tensor<T> forward(tensor<T> input){
            auto t = input->expr(&std::tanh);
            t->computeGrad = input->computeGrad;
            if (t->computeGrad){
                t->initGraph({input.get()}, &backward);
            }
            return t;
        }

    };

    template<typename T>
    inline tensor<T> Tanh(tensor<T> input){
        return Tanh::forward(input);
    }

};
};

#endif // __CML_FUNCTIONS_NONLINEAR_TANH_H__
