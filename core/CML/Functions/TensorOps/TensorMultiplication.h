#ifndef __CML_FUNCTIONS_TENSOROPS_TENSOR_MULTIPLICATION_H__
#define __CML_FUNCTIONS_TENSOROPS_TENSOR_MULTIPLICATION_H__

#include "TensorOps.h"

namespace cml {

    template<typename T>
    std::vector<tensor<T>> matmul_backward(std::vector<tensor<T>>& params, std::vector<tensor<T>> output){
#ifdef DEBUG
        using namespace std;
        cout << "Matrix Multiplication Backward" << endl;
#endif
        auto lhs = params.at(0);
        auto rhs = params.at(1);
        auto output_grad = output.at(0);
        tensor<T> lhs_grad = nullptr;
        tensor<T> rhs_grad = nullptr;

        if (lhs->computeGrad){
            lhs_grad = make_tensor<T>(static_cast<DMatrix<T>>(
                // TODO:  Check to see if order is correct
                output_grad->matrix() * rhs->matrix().transpose()
            ));
        }
        if (rhs->computeGrad){
            rhs_grad = make_tensor<T>(static_cast<DMatrix<T>>(
                // TODO:  Check to see if order is correct
                lhs->matrix().transpose() * output_grad->matrix()
            ));
        }

        return {lhs_grad, rhs_grad};
    }
    template<typename T>
    tensor<T> matmul(tensor<T> lhs, tensor<T> rhs){
        auto t = make_tensor<T>(static_cast<DMatrix<T>>(
            lhs->matrix() * rhs->matrix()
        ), lhs->computeGrad || rhs->computeGrad);

        if (t->computeGrad){
            t->initGraph({lhs, rhs}, matmul_backward<T>);
        }

        return t;
    }

    /*  
        Coefficient wise multiplication
     */
    template<typename T>
    std::vector<tensor<T>> multiply_backward(std::vector<tensor<T>>& params, std::vector<tensor<T>> output){
#ifdef DEBUG
        using namespace std;
        cout << "Tensor Multiplication Backward" << endl;
#endif
        auto lhs = params.at(0);
        auto rhs = params.at(1);
        auto output_grad = output.at(0);
        tensor<T> lhs_grad = nullptr;
        tensor<T> rhs_grad = nullptr;

        if (lhs->computeGrad){
            lhs_grad = lhs->empty();
            lhs_grad->matrix() = rhs->matrix().array() * output_grad->matrix().array();
        }
        if (rhs->computeGrad){
            rhs_grad = rhs->empty();
            rhs_grad->matrix() = lhs->matrix().array() * output_grad->matrix().array();
        }

        return {lhs_grad, rhs_grad};
    }
    template<typename T>
    tensor<T> multiply(tensor<T> lhs, tensor<T> rhs){

        if (lhs->shape() != rhs->shape()){
            throw CMLException("Tensor Multiplication:  Shapes do not match:  ",  lhs->shape(),  "!=",  rhs->shape());
        }

        auto t = lhs->empty(lhs->computeGrad || rhs->computeGrad);
        t->matrix() = lhs->matrix().array() * rhs->matrix().array();

        if (t->computeGrad){
            t->initGraph({lhs, rhs}, multiply_backward<T>);
        }

        return t;
    }


}

#endif // __CML_FUNCTIONS_TENSOROPS_TENSOR_MULTIPLICATION_H__
