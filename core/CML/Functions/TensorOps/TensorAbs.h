#ifndef __CML_FUNCTIONS_TENSOROPS_TENSORABS_H__
#define __CML_FUNCTIONS_TENSOROPS_TENSORABS_H__

#include "../../Tensors/Tensor.h"

namespace cml {

    struct TensorAbs {
        
        template<typename T>
        static T gradient(const T& x){
            return (T)(x < 0 ? 0 : 1);
        }
        
        template<typename T>
        static std::vector<tensor<T>> backward(std::vector<tensor<T>>& params, std::vector<tensor<T>> output){
            tensor<T> output_grad = output.at(0);
            tensor<T> input_grad = output_grad->expr(&gradient);
            return {input_grad};
        }

        template<typename T>
        static tensor<T> forward(tensor<T> input){
            auto t = input->empty(input->computeGrad);
            t->matrix() = input->matrix().abs();
            
            if (t->computeGrad){
                t->initGraph({input}, &backward);
            }
            return t;
        }
    };

    template<typename T, int nDims>
    inline tensor<T> abs(tensor<T> input){
        return TensorAbs::forward(input);
    }

}

#endif // __CML_FUNCTIONS_TENSOROPS_TENSORABS_H__
