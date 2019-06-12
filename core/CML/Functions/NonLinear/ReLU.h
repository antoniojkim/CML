#ifndef __CML_FUNCTIONS_NONLINEAR_RELU_H__
#define __CML_FUNCTIONS_NONLINEAR_RELU_H__

#include "../../Tensor.h"
#include "../../DCG.h"

namespace cml {
namespace Function {
    
    struct ReLU {
        
        template<typename T>
        static tensor<T> forward(tensor<T> input){
            auto t = make_tensor<T>(static_cast<DMatrix<T>>(
                input->array().abs()
            ));
            t->computeGrad = input->computeGrad;
            if (t->computeGrad){
                t->initGraph([input, t](tensor<T> output) -> void {
                    // // std::cout << "ReLU.output:" << std::endl << output << std::endl;
                    // auto u = make_tensor<T>(static_cast<DMatrix<T>>(
                    //     input->unaryExpr([](T x){ return (T)(x > 0 ? 1 : 0); }).array() *
                    //     output->array()
                    // ));
                    // // std::cout << "ReLU.u:" << std::endl << u << std::endl;
                    // return u;
                });
            }
            return t;
        }

    };

    template<typename T>
    inline tensor<T> ReLU(tensor<T> input){
        return ReLU::forward(input);
    }

};
};

#endif // __CML_FUNCTIONS_NONLINEAR_H__
