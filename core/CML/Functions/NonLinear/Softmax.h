#ifndef __CML_FUNCTIONS_NONLINEAR_SOFTMAX_H__
#define __CML_FUNCTIONS_NONLINEAR_SOFTMAX_H__

#include <cmath>

#include "NonLinear.h"
#include "../../Tensors/Tensor.h"


namespace cml {
namespace Function {
    
    struct Softmax {
        
        template<typename T, int nDims>
        static tensor<T> forward(Tensor<T, nDims>* input){
            auto max = input->tensor().maximum();
            auto exps = input->tensor().unaryExpr([max](const T& x){
                return std::exp(x - max);
            });
            auto sum = exps.sum();
            auto t = make_tensor<T>(static_cast<Eigen::Tensor<T, nDims>>( exps / sum ));

            t->computeGrad = input->computeGrad;
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

    template<typename T, int nDims>
    inline tensor<T> Softmax(Tensor<T, nDims>* input){
        return Softmax::forward(input);
    }
    template<typename T>
    inline tensor<T> Softmax(tensor<T> input){
        return input->softmax();
    }

};
};

#endif // __CML_FUNCTIONS_NONLINEAR_SOFTMAX_H__
