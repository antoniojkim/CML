#ifndef __CML_FUNCTIONS_FUNCTION_H__
#define __CML_FUNCTIONS_FUNCTION_H__

#include "../Tensor.h"
#include "../DCG.h"

namespace cml {
namespace Function {

    struct Linear {

        template<typename T>
        static Tensor<T> backward(Tensor<T>& output){
            throw "Unimplemented Linear::backward(Tensor<T>& output)";
        }


        template<typename T>
        static Tensor<T> forward(Tensor<T>& input, Tensor<T>& weights){
            auto t = Tensor<T>(static_cast<DMatrix<T>>(
                input.data() * weights.data().transpose()
            ));
            t.graph = new DCG<T>(input.graph);
            t.graph->f = Linear::backward<T>;
            return t;
        }
        template<typename T>
        static Tensor<T> forward(Tensor<T>& input, Tensor<T>& weights, Tensor<T>& bias){
            auto t = Tensor<T>(static_cast<DMatrix<T>>(
                input.data() * weights.data().transpose() + bias.data()
            ));
            t.graph = new DCG<T>(input.graph);
            t.graph->f = Linear::backward<T>;
            return t;
        }
    };

};
};

#endif //__CML_FUNCTIONS_FUNCTION_H__ 
