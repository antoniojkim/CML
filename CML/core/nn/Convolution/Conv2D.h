#ifndef __CML_NN_CONVOLUTION_CONV2D_H__
#define __CML_NN_CONVOLUTION_CONV2D_H__

#include <cmath>

#include "../Modules.h"
#include "../../Tensor.h"
#include "../../Functions/Convolution/Conv2D.h"

namespace cml {

    namespace nn {

        template<typename T = float>
        class Conv2D: public Module<T> {

            using Module<T>::params;
            using Module<T>::addParameter;

            size_t inputChannels; // Number of channels in input image
            size_t outputChannels; // Number of channels in output image
            size_t kernelSize; // Size of the convolving kernel
            size_t stride; // Stride of the convolution. Default: 1
            size_t padding; // Zero-padding added to both sides of the input. Default: 0
            size_t dilation; // Spacing between kernel elements. Default: 1
            size_t groups; // Number of blocked connections from input channels to output channels. Default: 1
            bool bias; // If True, adds a learnable bias to the output. Default: True

            public:
                Conv2D(const size_t& inputChannels,
                    const size_t& outputChannels,
                    const size_t& kernelSize,
                    const size_t& stride = 1,
                    const size_t& padding = 0,
                    const size_t& dilation = 1,
                    const size_t& groups = 1,
                    const bool& bias = true):
                    inputChannels{inputChannels}, outputChannels{outputChannels},
                    kernelSize{kernelSize}, stride{stride}, padding{padding},
                    dilation{dilation}, groups{groups}, bias{bias} {

                    addParameter("weights", outputChannels, inputChannels/groups, kernelSize, kernelSize);
                    params[0]->randomize();  // Initialize Weights to random
                    params[0]->computeGrad = true;  // Enable automatic gradient calculation

                    // int H_out = floor((()/stride)+1)
                    if (bias){
                        addParameter("bias", outputChannels);
                        params[1]->randomize();  // Initialize Weights to random
                        params[1]->computeGrad = true;  // Enable automatic gradient calculation
                    }
                }

                Parameter<T>& getWeights(){ return params[0]; }
                Parameter<T>& getBias(){
                    if (bias) return params[1];
                    throw "Attempting to get bias from Conv2D layer without bias";
                }

                cml::tensor<T> forward(cml::tensor<T> x) override {
                    return bias ? Function::Conv2D::forward(x, getWeights(), getBias(), stride, padding, dilation) :
                                  Function::Conv2D::forward(x, getWeights(), (tensor<T>)(nullptr), stride, padding, dilation);
                }

                std::ostream& print(std::ostream& out, const std::string& indent) override {
                    return out << "Conv2D { inputChannels: " << inputChannels <<
                                        "  outputChannels: " << outputChannels <<
                                        "  kernelSize: " << kernelSize <<
                                        "  stride: " << stride <<
                                        "  padding: " << padding <<
                                        "  dilation: " << dilation <<
                                        "  groups: " << groups << "  bias: " << (bias ? "true" : "false") << " }";
                }



        };

    }
}

#endif // __CML_NN_CONVOLUTION_CONV2D_H__
