#ifndef __CML_FUNCTIONS_CONVOLUTION_CONV2D_H__
#define __CML_FUNCTIONS_CONVOLUTION_CONV2D_H__

#include <cmath>

#include "../../Tensor.h"

namespace cml {
namespace Function {

    struct Conv2D {

        template<typename T>
        static std::vector<tensor<T>> backward(std::vector<tensor<T>>& params, std::vector<tensor<T>> output){
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
        }

        template<typename T>
        static tensor<T> forward(tensor<T> input, tensor<T> weights, tensor<T> bias, const size_t& stride, const size_t& padding, const size_t& dilation){
            
            const size_t& N = input->shape()[0];
            const size_t& c_in = input->shape()[1];
            const size_t& h_in = input->shape()[2];
            const size_t& w_in = input->shape()[3];
            const size_t& outputChannels = weights->shape()[0];
            const size_t& kernelSize = weights->shape()[3];

            size_t h_out = (h_in + 2*padding - dilation*(kernelSize-1) - 1) / stride + 1;
            size_t w_out = (w_in + 2*padding - dilation*(kernelSize-1) - 1) / stride + 1;

            tensor<T> t = make_tensor<T>(std::vector<size_t>({N, outputChannels, h_out, w_out}));
            Eigen::array<ptrdiff_t, 4> dims({0, 1, 2, 3});
            t->toTensor<4>() = input->toTensor<4>().convolve(weights->toTensor<4>(), dims);

            t->computeGrad = input->computeGrad || weights->computeGrad || (bias != nullptr && bias->computeGrad);
            if (t->computeGrad){
                t->initGraph({input, weights, bias}, backward<T>);
            }
            return t;
        }
    };

    template<typename T>
    inline tensor<T> Conv2D(tensor<T> input, tensor<T> weights, tensor<T> bias, const size_t& stride, const size_t& padding, const size_t& dilation, const size_t& groups){
        return Conv2D::forward(input, weights, bias);
    }

};
};

#endif //__CML_FUNCTIONS_CONVOLUTION_CONV2D_H__
