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
                t->initGraph([input](tensor<T> output) -> void {
                    // return make_tensor<T>(static_cast<DMatrix<T>>(
                    //     input->unaryExpr([](T x){
                    //         auto coshx = cosh(x);
                    //         return (T)(1.0 / coshx*coshx);
                    //     }).array() * output->array()
                    // ));
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
