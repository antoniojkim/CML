#ifndef __CML_FUNCTIONS_NONLINEAR_SOFTMAX_H__
#define __CML_FUNCTIONS_NONLINEAR_SOFTMAX_H__

#include <cmath>

#include "NonLinear.h"
#include "../../Tensors/Tensor.h"


namespace cml {
namespace Function {
    
    struct Softmax {
        
        template<typename T>
        static tensor<T> forward(tensor<T> input){
            auto t = input->empty(input->computeGrad);

            auto max = input->matrix().maxCoeff();
            auto exps = (input->matrix().array() - max).exp();
            auto sum = exps.sum();
            t->matrix() = exps / sum;
            
            if (t->computeGrad){
                t->initGraph({input}, [t](std::vector<tensor<T>>& params, std::vector<tensor<T>> output) -> std::vector<tensor<T>> {
#ifdef DEBUG
                    using namespace std;
                    cout << "Softmax::backward" << endl;
#endif

                    tensor<T> output_grad = output.at(0);
                    if (t->cols() != 1) throw "Invalid shape for softmax_grad"; 

                    auto input_grad = make_tensor<T>(static_cast<DMatrix<T>>(
                        (static_cast<DMatrix<T>>(t->matrix().asDiagonal()) - 
                         (t->matrix() * t->matrix().transpose())) * output_grad->matrix()
                    ));

                    return {input_grad};
                });
            }
            return t;
        }

    };

    template<typename T>
    inline tensor<T> Softmax(tensor<T> input){
        return Softmax::forward(input);
    }

};
};

#endif // __CML_FUNCTIONS_NONLINEAR_SOFTMAX_H__
