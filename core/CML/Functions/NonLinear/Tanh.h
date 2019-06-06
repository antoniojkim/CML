#ifndef __CML_FUNCTIONS_NONLINEAR_TANH_H__
#define __CML_FUNCTIONS_NONLINEAR_TANH_H__

#include <cmath>

#include "../../Tensor.h"
#include "../../DCG.h"

namespace cml {
namespace Function {
    
    struct Tanh {
        
        template<typename T>
        static tensor<T> forward(tensor<T> input, const bool& createGraph = true){
            auto t = make_tensor<T>(static_cast<DMatrix<T>>(
                input->array().tanh()
            ));
            if (createGraph){
                t->graph = make_graph<T>(input->graph);
                t->graph->f = [input](tensor<T> output) -> tensor<T> {
                    if (output != nullptr){
                        return make_tensor<T>(static_cast<DMatrix<T>>(
                            input->unaryExpr([](T x){
                                auto coshx = cosh(x);
                                return (T)(1.0 / coshx*coshx);
                            }).array() * output->array()
                        ));
                    }
                    return make_tensor<T>(static_cast<DMatrix<T>>(
                        input->unaryExpr([](T x){
                            auto coshx = cosh(x);
                            return (T)(1.0 / coshx*coshx);
                        })
                    ));
                };
            }
            return t;
        }

    };

    template<typename T>
    inline tensor<T> Tanh(tensor<T> input, const bool& createGraph = true){
        return Tanh::forward(input, createGraph);
    }

};
};

#endif // __CML_FUNCTIONS_NONLINEAR_TANH_H__
