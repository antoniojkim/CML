#ifndef __CML_FUNCTIONS_LINEAR_LINEAR_H__
#define __CML_FUNCTIONS_LINEAR_LINEAR_H__

#include "../../Tensors/Tensor2D.h"

namespace cml {
namespace Function {

    struct Linear {

        template<typename T>
        static tensor<T> forward(tensor2d<T> input, tensor<T> weights, tensor<T> bias = nullptr){
            tensor<T> t = nullptr;
            if (bias != nullptr)
                t = make_tensor<T>(static_cast<DMatrix<T>>(
                    (weights->data().transpose() * input->data()).colwise() + bias->data().col(0)
                ));
            else
                t = make_tensor<T>(static_cast<DMatrix<T>>(
                    weights->data().transpose() * input->data()
                ));

            t->computeGrad = input->computeGrad || weights->computeGrad || (bias != nullptr && bias->computeGrad);
            if (t->computeGrad){
                t->initGraph({input, weights, bias}, [](std::vector<tensor<T>>& params, 
                                                        std::vector<tensor<T>> output) -> std::vector<tensor<T>>{
#ifdef DEBUG
                    using namespace std;
                    cout << "Linear::backward()" << endl;
#endif
                    tensor<T> input = params.at(0);
                    tensor<T> weights = params.at(1);
                    tensor<T> bias = params.at(2);
                    tensor<T> output_grad = output.at(0);
                    tensor<T> input_grad = nullptr;
                    tensor<T> weight_grad = nullptr;
                    tensor<T> bias_grad = nullptr;

                    if (input->computeGrad){
                        input_grad = make_tensor<T>(static_cast<DMatrix<T>>(
                            // TODO:  Check to see if order is correct
                            weights->data() * output_grad->data()
                        ));
                    }
                    if (weights->computeGrad){
                        weight_grad = make_tensor<T>(static_cast<DMatrix<T>>(
                            // TODO:  Check to see if order is correct
                            input->data() * output_grad->data().transpose()
                        ));
                    }
                    if (bias != nullptr && bias->computeGrad){
                        bias_grad = make_tensor<T>(static_cast<DMatrix<T>>(
                            output_grad->data().rowwise().sum()
                        ));
                    }

                    return {input_grad, weight_grad, bias_grad};
                });
            }
            return t;
        }
        
        template<typename T>
        static tensor<T> forward(tensor<T> input, tensor<T> weights, tensor<T> bias = nullptr){
            switch(input->getType()){
                case TensorType::MATRIX:
                    return forward(std::static_pointer_cast<Tensor2D<T>>(input), weights, bias);
                default:
                    throw UnsupportedOperationException("Linear unsupported on Tensor type");
            }
        }
    };

    template<typename T>
    inline tensor<T> Linear(tensor<T> input, tensor<T> weights, tensor<T> bias = nullptr){
        return Linear::forward(input, weights, bias);
    }

};
};

#endif //__CML_FUNCTIONS_LINEAR_LINEAR_H__ 
