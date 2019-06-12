#ifndef __CML_FUNCTIONS_NONLINEAR_SIGMOID_H__
#define __CML_FUNCTIONS_NONLINEAR_SIGMOID_H__

#include <cmath>

#include "../../Tensor.h"
#include "../../DCG.h"

namespace cml {
namespace Function {
    
    struct Sigmoid {
        
        template<typename T>
        static tensor<T> forward(tensor<T> input){
            auto t = make_tensor<T>(static_cast<DMatrix<T>>(
                input->unaryExpr([](T x){ return (T)(1.0 / (1.0 + exp(-x))); })
            ));
            t->computeGrad = input->computeGrad;
            if (t->computeGrad){
                t->initGraph([input](tensor<T> output) -> void {
                    // return make_tensor<T>(static_cast<DMatrix<T>>(
                    //     input->unaryExpr([](T x){
                    //         auto y = (T)(1.0 / (1.0 + exp(-x)));
                    //         return y*(1-y);
                    //     }).array() * output->array()
                    // ));
                });
            }
            return t;
        }

    };

    template<typename T>
    inline tensor<T> Sigmoid(tensor<T> input){
        return Sigmoid::forward(input);
    }

};
};

#endif // __CML_FUNCTIONS_NONLINEAR_SIGMOID_H__
