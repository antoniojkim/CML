#ifndef __CML_FUNCTIONS_LINEAR_H__
#define __CML_FUNCTIONS_LINEAR_H__

#include "../Tensor.h"
#include "../DCG.h"
#include "../nn/Parameter.h"

namespace cml {
namespace Function {

    struct Linear {

        template<typename T>
        static tensor<T> forward(tensor<T> input, nn::Parameter<T>& weights){
            auto t = make_tensor<T>(static_cast<DMatrix<T>>(
                input->data() * weights.data().transpose()
            ));
            t->graph = make_graph<T>(input->graph);
            t->graph->f = [input, t](tensor<T> output) -> tensor<T>{
                throw "Unimplemented weights only Linear::backward(Tensor<T>& output)";
            };
            return t;
        }
        template<typename T>
        static tensor<T> forward(tensor<T> input, nn::Parameter<T>& weights, nn::Parameter<T>& bias){
            auto t = make_tensor<T>(static_cast<DMatrix<T>>(
                input->data() * weights.data().transpose() + bias.data()
            ));
            t->graph = make_graph<T>(input->graph);
            t->graph->f = [input, t](tensor<T> output) -> tensor<T>{
                throw "Unimplemented weights and bias Linear::backward(tensor<T>& output)";
            };
            return t;
        }
    };

    template<typename T>
    inline tensor<T> Linear(tensor<T> input, nn::Parameter<T>& weights){
        return Linear::forward(input, weights);
    }
    template<typename T>
    inline tensor<T> Linear(tensor<T> input, nn::Parameter<T>& weights, nn::Parameter<T>& bias){
        return Linear::forward(input, weights, bias);
    }

};
};

#endif //__CML_FUNCTIONS_LINEAR_H__ 
