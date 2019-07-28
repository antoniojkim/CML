#ifndef __CML_FUNCTIONS_NONLINEAR_SIGMOID_H__
#define __CML_FUNCTIONS_NONLINEAR_SIGMOID_H__

#include <cmath>

#include "../../Tensors/Tensor2D.h"


namespace cml {
namespace Function {
    
    struct Sigmoid {
        
        template<typename T>
        static tensor<T> forward(tensor2d<T> input){
            auto t = make_tensor<T>(static_cast<DMatrix<T>>(
                input->data().unaryExpr([](T x){ return (T)(1.0 / (1.0 + exp(-x))); })
            ));
            t->computeGrad = input->computeGrad;
            if (t->computeGrad){
                t->initGraph({input}, [](std::vector<tensor<T>>& params, std::vector<tensor<T>> output) -> std::vector<tensor<T>> {
#ifdef DEBUG
                    using namespace std;
                    cout << "Sigmoid::backward()" << endl;
#endif
                    tensor<T> input = params.at(0);
                    tensor<T> output_grad = output.at(0);
#ifdef DEBUG
                    cout << "    input:  " << input->rows() << ", " << input->cols() << endl;
                    cout << "    output:  " << output_grad->rows() << ", " << output_grad->cols() << endl;
#endif
                    tensor<T> input_grad = make_tensor<T>(static_cast<DMatrix<T>>(
                        input->data().unaryExpr([](T x){
                            auto y = (T)(1.0 / (1.0 + exp(-x)));
                            return y*(1-y);
                        }).array() * output_grad->data().array()
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
                    throw UnsupportedOperationException("Sigmoid unsupported on Tensor type");
            }
        }

    };

    template<typename T>
    inline tensor<T> Sigmoid(tensor<T> input){
        return Sigmoid::forward(input);
    }

};
};

#endif // __CML_FUNCTIONS_NONLINEAR_SIGMOID_H__
