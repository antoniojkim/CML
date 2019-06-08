#ifndef __CML_FUNCTIONS_LINEAR_H__
#define __CML_FUNCTIONS_LINEAR_H__

#include "../Tensor.h"
#include "../DCG.h"
#include "../nn/Parameter.h"

namespace cml {
namespace Function {

    struct Linear {

        template<typename T>
        static tensor<T> forward(tensor<T> input, nn::Parameter<T>& weights, const bool& createGraph = true){
            auto t = make_tensor<T>(static_cast<DMatrix<T>>(
                weights.transpose() * input->data()
            ));
            if (createGraph){
                t->graph = make_graph<T>(input->graph);
                t->graph->f = [input, &weights](tensor<T> output) -> tensor<T>{
                    auto dw = make_tensor<T>(static_cast<DMatrix<T>>(
                        input->array() * output->array()
                    ));
                    weights += dw;

                    return make_tensor<T>(static_cast<DMatrix<T>>(
                        weights.transpose().array() * output->array()
                    ));
                };
            }
            return t;
        }
        template<typename T>
        static tensor<T> forward(tensor<T> input, nn::Parameter<T>& weights, nn::Parameter<T>& bias, const bool& createGraph = true){
            auto t = make_tensor<T>(static_cast<DMatrix<T>>(
                weights.transpose() * input->data() + bias.data()
            ));
            if (createGraph){
                t->graph = make_graph<T>(input->graph);
                t->graph->f = [input, &weights](tensor<T> output) -> tensor<T>{
                    auto dw = make_tensor<T>(static_cast<DMatrix<T>>(
                        input->array() * output->array()
                    ));
                    weights += dw;

                    weights += output; // d(bias) = 1*output

                    return make_tensor<T>(static_cast<DMatrix<T>>(
                        weights.transpose().array() * output->array()
                    ));
                };
            }
            return t;
        }
    };

    template<typename T>
    inline tensor<T> Linear(tensor<T> input, nn::Parameter<T>& weights, const bool& createGraph = true){
        return Linear::forward(input, weights, createGraph);
    }
    template<typename T>
    inline tensor<T> Linear(tensor<T> input, nn::Parameter<T>& weights, nn::Parameter<T>& bias, const bool& createGraph = true){
        return Linear::forward(input, weights, bias, createGraph);
    }

};
};

#endif //__CML_FUNCTIONS_LINEAR_H__ 
