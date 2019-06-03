#ifndef __CML_FUNCTIONS_NONLINEAR_SIGMOID_H__
#define __CML_FUNCTIONS_NONLINEAR_SIGMOID_H__

#include <cmath>

#include "../../Tensor.h"
#include "../../DCG.h"

namespace cml {
namespace Function {
    
    struct Sigmoid {
        
        template<typename T>
        static Tensor<T> backward(Tensor<T>& output){
            throw "Unimplemented Sigmoid::backward(Tensor<T>& output)";
        }
        
        template<typename T>
        static Tensor<T> forward(Tensor<T>& input){
            auto t = Tensor<T>(static_cast<DMatrix<T>>(
                input.data().unaryExpr([](T x){ return (T)(1.0 / (1.0 + exp(-x))); })
            ));
            t.graph = new DCG<T>(input.graph);
            t.graph->f = Sigmoid::backward<T>;
            return t;
        }

    };

    template<typename T>
    inline Tensor<T> Sigmoid(Tensor<T>& input){ return Sigmoid::forward(input); }

};
};

#endif // __CML_FUNCTIONS_NONLINEAR_SIGMOID_H__
