#ifndef __CML_FUNCTIONS_NONLINEAR_RELU_H__
#define __CML_FUNCTIONS_NONLINEAR_RELU_H__

#include <functional>

#include "../../Tensor.h"


namespace cml {
namespace Function {
    
    struct ReLU {
        
        template<typename T>
        static T gradient(const T& x){
            return (T)(x < 0 ? 0 : 1);
        }
        
        template<typename T>
        static std::vector<tensor<T>> backward(std::vector<tensor<T>>& params, std::vector<tensor<T>> output){
            tensor<T> output_grad = output.at(0);
            tensor<T> input_grad = output_grad->copy(&gradient);
            return {input_grad};
        }
        
        template<typename T>
        static tensor<T> forward(tensor<T> input){
            auto t = input->abs();
            t->computeGrad = input->computeGrad;
            if (t->computeGrad){
                t->initGraph({input}, &backward);
            }
            return t;
        }
        
        template<typename T>
        static tensor<T> forward(tensor<T> input){
            switch(input->getType()){
                case TensorType::MATRIX:
                    return forward(std::static_pointer_cast<Tensor2D<T>>(input));
                default:
                    throw UnsupportedOperationException("ReLU unsupported on tensor type");
            }
        }

    };

    template<typename T>
    inline tensor<T> ReLU(tensor<T> input){
        return ReLU::forward(input);
    }

};
};

#endif // __CML_FUNCTIONS_NONLINEAR_H__
