#ifndef __CML_FUNCTIONS_CONVOLUTION_CONV2D_H__
#define __CML_FUNCTIONS_CONVOLUTION_CONV2D_H__

#include "../../Tensor.h"
#include "../../DCG.h"

namespace cml {
namespace Function {

    struct Conv2D {

        template<typename T>
        static tensor<T> forward(tensor<T> input, tensor<T> weights, tensor<T> bias = nullptr){
            tensor<T> t = nullptr;

            t->computeGrad = input->computeGrad || weights->computeGrad || (bias != nullptr && bias->computeGrad);
            if (t->computeGrad){
                t->initGraph({input, weights, bias}, [](std::vector<tensor<T>>& params, 
                                                        std::vector<tensor<T>> output) -> std::vector<tensor<T>>{
#ifdef DEBUG
                    using namespace std;
                    cout << "Conv2D::backward()" << endl;
#endif
                    tensor<T> input = params.at(0);
                    tensor<T> weights = params.at(1);
                    tensor<T> bias = params.at(2);
                    tensor<T> output_grad = output.at(0);
                    tensor<T> input_grad = nullptr;
                    tensor<T> weight_grad = nullptr;
                    tensor<T> bias_grad = nullptr;

                    // if (input->computeGrad){
                    //     input_grad = make_tensor<T>(static_cast<DMatrix<T>>(
                    //         // TODO:  Check to see if order is correct
                    //         weights->data() * output_grad->data()
                    //     ));
                    // }
                    // if (weights->computeGrad){
                    //     weight_grad = make_tensor<T>(static_cast<DMatrix<T>>(
                    //         // TODO:  Check to see if order is correct
                    //         input->data() * output_grad->transpose()
                    //     ));
                    // }
                    // if (bias != nullptr && bias->computeGrad){
                    //     bias_grad = make_tensor<T>(static_cast<DMatrix<T>>(
                    //         output_grad->rowwise().sum()
                    //     ));
                    // }

                    return {input_grad, weight_grad, bias_grad};
                });
            }
            return t;
        }
    };

    template<typename T>
    inline tensor<T> Conv2D(tensor<T> input, tensor<T> weights, tensor<T> bias = nullptr){
        return Conv2D::forward(input, weights, bias);
    }

};
};

#endif //__CML_FUNCTIONS_CONVOLUTION_CONV2D_H__ 
