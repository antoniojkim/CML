#ifndef __CML_FUNCTIONS_NONLINEAR_RELU_H__
#define __CML_FUNCTIONS_NONLINEAR_RELU_H__

#include "../../Tensor.h"
#include "../../DCG.h"

namespace cml {
namespace Function {
    
    struct ReLU {
        
        template<typename T>
        static tensor<T> forward(tensor<T> input, const bool& createGraph = true){
            auto t = make_tensor<T>(static_cast<DMatrix<T>>(
                input->array().abs()
            ));
            if (createGraph){
                t->graph = make_graph<T>(input->graph);
                t->graph->f = [input, t](tensor<T> output) -> tensor<T> {
                    if (output != nullptr){
                        return make_tensor<T>(static_cast<DMatrix<T>>(
                            input->unaryExpr([](T x){ return (T)(x > 0 ? 1 : 0); }).array() *
                            output->array()
                        ));
                    }
                    return make_tensor<T>(static_cast<DMatrix<T>>(
                        input->unaryExpr([](T x){ return (T)(x > 0 ? 1 : 0); })
                    ));
                };
            }
            return t;
        }

    };

    template<typename T>
    inline tensor<T> ReLU(tensor<T> input, const bool& createGraph = true){
        return ReLU::forward(input, createGraph);
    }

};
};

#endif // __CML_FUNCTIONS_NONLINEAR_H__
