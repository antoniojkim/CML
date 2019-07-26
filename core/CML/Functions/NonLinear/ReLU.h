#ifndef __CML_FUNCTIONS_NONLINEAR_RELU_H__
#define __CML_FUNCTIONS_NONLINEAR_RELU_H__

#include "../../Tensor.h"


namespace cml {
namespace Function {
    
    struct ReLU {
        
        template<typename T>
        static tensor<T> forward(tensor2d<T> input){
            auto t = make_tensor<T>(static_cast<DMatrix<T>>(
                input->data().array().abs()
            ));
            t->computeGrad = input->computeGrad;
            if (t->computeGrad){
                t->initGraph({input}, [](std::vector<tensor<T>>& params, std::vector<tensor<T>> output) -> std::vector<tensor<T>> {
                    tensor<T> output_grad = output.at(0);
                    tensor<T> input_grad = make_tensor<T>(static_cast<DMatrix<T>>(
                        output_grad->data().unaryExpr([](T x){ return (T)(x < 0 ? 0 : 1); }).array()
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
                    throw UnsupportedOperationException("ReLU unsupported on tensor type");
            }
        }

    };

    template<typename T>
    inline tensor<T> ReLU(tensor<T> input){
        return ReLU::forward(input);
    }

};
};

#endif // __CML_FUNCTIONS_NONLINEAR_H__
