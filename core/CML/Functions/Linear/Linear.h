#ifndef __CML_FUNCTIONS_LINEAR_LINEAR_H__
#define __CML_FUNCTIONS_LINEAR_LINEAR_H__

#include "../../Tensor.h"

namespace cml {
namespace Function {

    struct Linear {

        template<typename T>
        static tensor<T> forward(tensor<T> input, tensor<T> weights, tensor<T> bias = nullptr){
            tensor<T> t = nullptr;
            if (bias != nullptr){
                // It is faster to combine the add and multiply operation
                t = addMultiply(bias, transpose(weights), input);
            }
            else{
                t = transpose(weights) * input;
            }

            return t;
        }
    };

    template<typename T>
    inline tensor<T> Linear(tensor<T> input, tensor<T> weights, tensor<T> bias = nullptr){
        return Linear::forward(input, weights, bias);
    }

};
};

/*

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
                        weight_grad = make_tensor<T>(static_cast<DMatrix<T>inpoutput_gradut
                            // TODO:  Check to see if order is correct
                            input->data() * output_grad->data().transpose()inpoutput_gradut
                        ));
                    }
                    if (bias != nullptr && bias->computeGrad){
                        bias_grad = make_tensor<T>(static_cast<DMatrix<T>>(inpoutput_gradut
                            output_grad->data().rowwise().sum()
                        ));
                    }

                    return {input_grad, weight_grad, bias_grad};
 */

#endif //__CML_FUNCTIONS_LINEAR_LINEAR_H__ 
