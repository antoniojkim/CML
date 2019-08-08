#ifndef __CML_NN_CONVOLUTION_CONV2D_H__
#define __CML_NN_CONVOLUTION_CONV2D_H__

#include <cmath>

#include "../../Modules.h"
#include "../../Tensors/Tensor.h"
#include "../../Functions/Convolution/Conv2D.h"

namespace cml {

    namespace nn {

        template<typename T = float>
        class Conv2D: public Module<T> {

            unsigned int inputChannels; // Number of channels in input image
            unsigned int outputChannels; // Number of channels in output image
            unsigned int kernelSize; // Size of the convolving kernel
            unsigned int stride; // Stride of the convolution. Default: 1
            unsigned int padding; // Zero-padding added to both sides of the input. Default: 0
            unsigned int dilation; // Spacing between kernel elements. Default: 1
            unsigned int groups; // Number of blocked connections from input channels to output channels. Default: 1
            bool bias; // If True, adds a learnable bias to the output. Default: True

            tensor<T> weights;
            tensor<T> bias;

            public:
                Conv2D(const unsigned int& inputChannels,
                    const unsigned int& outputChannels,
                    const unsigned int& kernelSize,
                    const unsigned int& stride = 1,
                    const unsigned int& padding = 0,
                    const unsigned int& dilation = 1,
                    const unsigned int& groups = 1,
                    const bool& bias = true):
                    inputChannels{inputChannels}, outputChannels{outputChannels},
                    kernelSize{kernelSize}, stride{stride}, padding{padding},
                    dilation{dilation}, groups{groups}, 
                    weights{make_tensor<T>(out_channels, in_channels/groups, kernelSize, kernelSize)} {
                    int H_out = floor((()/stride)+1)
                    if (bias){
                        this->bias = make_tensor<T>(out_channels);
                    }
                }

                Parameter<T>& getWeights(){ return params[0]; }
                Parameter<T>& getBias(){
                    if (bias) return params[1];
                    throw "Attempting to get bias from Linear layer without bias";
                }

                cml::tensor<T> forward(cml::tensor<T> x) override {
                    return bias ? Function::Conv2D::forward(x, getWeights(), getBias()) :
                                  Function::Conv2D::forward(x, getWeights());
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
