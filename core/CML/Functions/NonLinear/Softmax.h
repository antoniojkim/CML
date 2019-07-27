#ifndef __CML_FUNCTIONS_NONLINEAR_SOFTMAX_H__
#define __CML_FUNCTIONS_NONLINEAR_SOFTMAX_H__

#include <cmath>

#include "../../Tensors/Tensor2D.h"


namespace cml {
namespace Function {
    
    struct Softmax {
        
        template<typename T>
        static tensor<T> forward(tensor2d<T> input){
            auto max = input->data().maxCoeff();
            auto exps = (input->data().array() - max).exp();
            auto sum = exps.sum();
            auto t = make_tensor<T>(static_cast<DMatrix<T>>( exps / sum ));

            t->computeGrad = input->computeGrad;
            if (t->computeGrad){
                t->initGraph({input}, [t](std::vector<tensor<T>>& params, std::vector<tensor<T>> output) -> std::vector<tensor<T>> {
#ifdef DEBUG
                    using namespace std;
                    cout << "Softmax::backward" << endl;
#endif

                    tensor<T> output_grad = output.at(0);
                    if (t->data().cols() != 1) throw "Invalid shape for softmax_grad"; 

                    auto input_grad = make_tensor<T>(static_cast<DMatrix<T>>(
                        (static_cast<DMatrix<T>>(t->data().asDiagonal()) - 
                         (t->data() * t->data().transpose())) * output_grad->data()
                    ));

                    return {input_grad};
                });
            }
            return t;
        }
        
        template<typename T>
        static tensor<T> forward(tensor<T> input){
            switch(input->getType()){
                case TensorType::MATRIX:
                    return forward(std::static_pointer_cast<Tensor2D<T>>(input));
                default:
                    throw UnsupportedOperationException("Softmax unsupported on Tensor type");
            }
        }

    };

    template<typename T = float>
    inline tensor<T> Softmax(tensor<T> input){
        return Softmax::forward(input);
    }

};
};

#endif // __CML_FUNCTIONS_NONLINEAR_SOFTMAX_H__
