#ifndef __CML_FUNCTIONS_NONLINEAR_TANH_H__
#define __CML_FUNCTIONS_NONLINEAR_TANH_H__

#include <cmath>

#include "../../Tensor.h"
#include "../../DCG.h"

namespace cml {
namespace Function {
    
    struct Tanh {
        
        template<typename T>
        static tensor<T> backward(tensor<T> output){
            throw "Unimplemented Tanh::backward(tensor<T>& output)";
        }
        
        template<typename T>
        static tensor<T> forward(tensor<T>& input){
            auto t = make_tensor<T>(static_cast<DMatrix<T>>(
                input->data().unaryExpr([](T x) -> T { return (T)tanh(x); })
            ));
            t->graph = make_graph<T>(input->graph);
            t->graph->f = Tanh::backward<T>;
            return t;
        }

    };

    template<typename T>
    inline tensor<T> Tanh(tensor<T>& input){ return Tanh::forward(input); }

};
};

#endif // __CML_FUNCTIONS_NONLINEAR_TANH_H__
