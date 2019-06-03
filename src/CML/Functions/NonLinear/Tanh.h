#ifndef __CML_FUNCTIONS_NONLINEAR_TANH_H__
#define __CML_FUNCTIONS_NONLINEAR_TANH_H__

#include <cmath>

#include "../../Tensor.h"
#include "../../DCG.h"

namespace cml {
namespace Function {
    
    struct Tanh {
        
        template<typename T>
        static Tensor<T> backward(Tensor<T>& output){
            throw "Unimplemented Tanh::backward(Tensor<T>& output)";
        }
        
        template<typename T>
        static Tensor<T> forward(Tensor<T>& input){
            auto t = Tensor<T>(static_cast<DMatrix<T>>(
                input.data().unaryExpr([](T x) -> T { return (T)tanh(x); })
            ));
            t.graph = new DCG<T>(input.graph);
            t.graph->f = Tanh::backward<T>;
            return t;
        }

    };

    template<typename T>
    inline Tensor<T> Tanh(Tensor<T>& input){ return Tanh::forward(input); }

};
};

#endif // __CML_FUNCTIONS_NONLINEAR_TANH_H__
