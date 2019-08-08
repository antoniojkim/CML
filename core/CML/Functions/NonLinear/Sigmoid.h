#ifndef __CML_FUNCTIONS_NONLINEAR_SIGMOID_H__
#define __CML_FUNCTIONS_NONLINEAR_SIGMOID_H__

#include <cmath>

#include "NonLinear.h"
#include "../../Tensors/TensorBase.h"


namespace cml {
namespace Function {
    
    struct Sigmoid {
        
        template<typename T>
        T sigmoid(const T& x){
            return (T)(1.0 / (1.0 + exp(-x)));
        }
        template<typename T>
        T gradient(const T& x){
            auto y = (T)(1.0 / (1.0 + exp(-x)));
            return y*(1-y);
        }
        
        template<typename T>
        std::vector<tensor<T>> backward(std::vector<_tensor_<T>>& params, std::vector<tensor<T>> output) {
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
            tensor<T> input_grad = input->expr(&gradient) * output_grad;
            return {input_grad};
        }
        
        template<typename T>
        static tensor<T> forward(tensor<T> input){
            auto t = input->expr(&sigmoid);
            t->computeGrad = input->computeGrad;
            if (t->computeGrad){
                t->initGraph({input.get()}, &backward);
            }
            return t;
        }

    };

    template<typename T>
    inline tensor<T> Sigmoid(tensor<T> input){
        return Sigmoid::forward(input);
    }

};
};

#endif // __CML_FUNCTIONS_NONLINEAR_SIGMOID_H__
