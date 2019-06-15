#ifndef __CML_FUNCTIONS_NONLINEAR_TANH_H__
#define __CML_FUNCTIONS_NONLINEAR_TANH_H__

#include <cmath>

#include "../../Tensor.h"
#include "../../DCG.h"

namespace cml {
namespace Function {
    
    struct Tanh {
        
        template<typename T>
        static tensor<T> forward(tensor<T> input){
            auto t = make_tensor<T>(static_cast<DMatrix<T>>(
                input->array().tanh()
            ));
            t->computeGrad = input->computeGrad;
            if (t->computeGrad){
                t->initGraph({input}, [](std::vector<tensor<T>>& params, std::vector<tensor<T>> output) -> std::vector<tensor<T>> {
                    tensor<T> output_grad = output.at(0);
                    tensor<T> input_grad = make_tensor<T>(static_cast<DMatrix<T>>(
                        output_grad->unaryExpr([](T x){
                            auto coshx = cosh(x);
                            return (T)(1.0 / coshx*coshx);
                        })
                    ));
                    return {input_grad};
                });
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
