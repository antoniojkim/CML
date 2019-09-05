#ifndef __CML_FUNCTIONS_NONLINEAR_SIGMOID_H__
#define __CML_FUNCTIONS_NONLINEAR_SIGMOID_H__

#include <cmath>

#include "NonLinear.h"
#include "../../Tensor.h"


namespace cml {
namespace Function {

    struct Sigmoid {

        template<typename T>
        static T sigmoid(const T& x){
            return (T)(1.0 / (1.0 + exp(-x)));
        }
        template<typename T>
        static T gradient(const T& x){
            auto y = (T)(1.0 / (1.0 + exp(-x)));
            return y*(1-y);
        }

        template<typename T>
        static std::vector<tensor<T>> backward(std::vector<tensor<T>>& params, std::vector<tensor<T>> output) {
            tensor<T> input = params.at(0);
            tensor<T> output_grad = output.at(0);
#ifdef DEBUG
            using namespace std;
            cout << "Sigmoid::backward()" << endl;
            cout << "    input:  " << input->rows() << ", " << input->cols() << endl;
            cout << "    output:  " << output_grad->rows() << ", " << output_grad->cols() << endl;
#endif
            tensor<T> input_grad = make_tensor<T>(static_cast<DMatrix<T>>(
                input->matrix().unaryExpr(std::ptr_fun(&gradient<T>)).array() * output_grad->matrix().array()
            ));
            return {input_grad};
        }

        template<typename T>
        static tensor<T> forward(tensor<T> input){
            auto t = input->expr(&sigmoid<T>);
            t->computeGrad = input->computeGrad;
            if (t->computeGrad){
                t->initGraph({input}, &backward<T>);
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
