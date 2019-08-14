#ifndef __CML_FUNCTIONS_TENSOROPS_TENSOR_MULTIPLICATION_H__
#define __CML_FUNCTIONS_TENSOROPS_TENSOR_MULTIPLICATION_H__

#include "TensorOps.h"

namespace cml {

    template<typename T>
    tensor<T> matmul(TensorBase<T>* lhs, TensorBase<T>* rhs){
        auto t = make_tensor<T>(static_cast<DMatrix<T>>(
            lhs->matrix() * rhs->matrix()
        ), lhs->computeGrad || rhs->computeGrad);

        if (t->computeGrad){
            t->initGraph({lhs, rhs}, [](std::vector<tensor<T>>& params, std::vector<tensor<T>> output) -> std::vector<tensor<T>> {
#ifdef DEBUG
                using namespace std;
                cout << "Tensor2D Multiplication Backward" << endl;
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
            });
        }

        return t;
    }

    /*  
        Coefficient wise multiplication
     */
    template<typename T, int nDims>
    tensor<T> multiply(Tensor<T, nDims>* lhs, Tensor<T, nDims>* rhs){
        auto t = make_tensor<T>(CAST_EIGEN_TENSOR(
            lhs->tensor() * rhs->tensor()
        ), lhs->computeGrad || rhs->computeGrad);

        if (t->computeGrad){
            t->initGraph({lhs, rhs}, [](std::vector<tensor<T>>& params, std::vector<tensor<T>> output) -> std::vector<tensor<T>> {
#ifdef DEBUG
                using namespace std;
                cout << "Tensor2D Multiplication Backward" << endl;
#endif
                auto lhs = params.at(0);
                auto rhs = params.at(1);
                tensor<T> lhs_grad = rhs;
                tensor<T> rhs_grad = lhs;

                return {lhs_grad, rhs_grad};
            });
        }

        return t;
    }


}

#endif // __CML_FUNCTIONS_TENSOROPS_TENSOR_MULTIPLICATION_H__
