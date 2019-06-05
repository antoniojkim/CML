#ifndef __CML_FUNCTIONS_NONLINEAR_SIGMOID_H__
#define __CML_FUNCTIONS_NONLINEAR_SIGMOID_H__

#include <cmath>

#include "../../Tensor.h"
#include "../../DCG.h"

namespace cml {
namespace Function {
    
    struct Sigmoid {
        
        template<typename T>
        static tensor<T> backward(tensor<T> output){
            throw "Unimplemented Sigmoid::backward(tensor<T>& output)";
        }
        
        template<typename T>
        static tensor<T> forward(tensor<T>& input){
            auto t = make_tensor<T>(static_cast<DMatrix<T>>(
                input->data().unaryExpr([](T x){ return (T)(1.0 / (1.0 + exp(-x))); })
            ));
            t->graph = make_graph<T>(input->graph);
            t->graph->f = Sigmoid::backward<T>;
            return t;
        }

    };

    template<typename T>
    inline tensor<T> Sigmoid(tensor<T>& input){ return Sigmoid::forward(input); }

};
};

#endif // __CML_FUNCTIONS_NONLINEAR_SIGMOID_H__
