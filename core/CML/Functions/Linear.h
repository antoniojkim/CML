#ifndef __CML_FUNCTIONS_LINEAR_H__
#define __CML_FUNCTIONS_LINEAR_H__

#include "../Tensor.h"
#include "../DCG.h"
// #include "../nn/Parameter.h"

namespace cml {
namespace Function {

    struct Linear {

        template<typename T>
        static tensor<T> forward(tensor<T> input, tensor<T> weights){
            auto t = make_tensor<T>(static_cast<DMatrix<T>>(
                weights->transpose() * input->data()
            ));
            t->computeGrad = input->computeGrad || weights->computeGrad;
            if (t->computeGrad){
                t->initGraph([input, weights](tensor<T> output) -> void{
                    auto dw = make_tensor<T>(static_cast<DMatrix<T>>(
                        input->array() * output->array()
                    ));
                    weights->graph()->accumulateGradient(dw);

                    // return make_tensor<T>(static_cast<DMatrix<T>>(
                    //     weights.transpose().array() * output->array()
                    // ));
                });
            }
            return t;
        }
        template<typename T>
        static tensor<T> forward(tensor<T> input, tensor<T> weights, tensor<T> bias){
            auto t = make_tensor<T>(static_cast<DMatrix<T>>(
                weights->transpose() * input->data() + bias->data()
            ));
            t->computeGrad = input->computeGrad || weights->computeGrad || bias->computeGrad;
            if (t->computeGrad){
                t->initGraph([input, weights, bias](tensor<T> output) -> void{
                    auto dw = make_tensor<T>(static_cast<DMatrix<T>>(
                        input->array() * output->array()
                    ));
                    weights->graph()->accumulateGradient(dw);

                    // bias += output; // d(bias) = 1*output

                    // return make_tensor<T>(static_cast<DMatrix<T>>(
                    //     weights.transpose().array() * output->array()
                    // ));
                });
            }
            return t;
        }
    };

    template<typename T>
    inline tensor<T> Linear(tensor<T> input, tensor<T> weights){
        return Linear::forward(input, weights);
    }
    template<typename T>
    inline tensor<T> Linear(tensor<T> input, tensor<T> weights, tensor<T> bias){
        return Linear::forward(input, weights, bias);
    }

};
};

#endif //__CML_FUNCTIONS_LINEAR_H__ 
