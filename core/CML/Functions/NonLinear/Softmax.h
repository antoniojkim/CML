#ifndef __CML_FUNCTIONS_NONLINEAR_SOFTMAX_H__
#define __CML_FUNCTIONS_NONLINEAR_SOFTMAX_H__

#include <cmath>

#include "../../Tensor.h"
#include "../../DCG.h"

namespace cml {
namespace Function {
    
    struct Softmax {
        
        template<typename T = float>
        static tensor<T> forward(tensor<T> input){
            auto max = input->maxCoeff();
            using namespace std;
            auto exps = (input->array() - max).exp();
            auto sum = exps.sum();
            auto t = make_tensor<T>(static_cast<DMatrix<T>>( exps / sum ));

            t->computeGrad = input->computeGrad;
            if (t->computeGrad){
                t->initGraph({input}, [t](std::vector<tensor<T>>& params, std::vector<tensor<T>> output) -> std::vector<tensor<T>> {
                    tensor<T> output_grad = output.at(0);

                    if (t->cols() != 1) throw "Invalid shape for softmax_grad"; 

                    auto input_grad  = nullptr;
                    // = make_tensor<float>(static_cast<DMatrix<float>>(
                    //     (static_cast<DMatrix<float>>(t->asDiagonal()) - 
                    //      (t->data() * t->transpose())) * output_grad->data()
                    // ));
                    return {input_grad};
                });
            }
            return t;
        }

    };

    template<typename T = float>
    inline tensor<T> Softmax(tensor<T> input){
        return Softmax::forward(input);
    }

};
};

#endif // __CML_FUNCTIONS_NONLINEAR_SOFTMAX_H__
