#ifndef __CML_FUNCTIONS_TENSOROPS_TENSOR_MULTIPLICATION_H__
#define __CML_FUNCTIONS_TENSOROPS_TENSOR_MULTIPLICATION_H__

#include "TensorOps.h"

namespace cml {

    template<typename T>
    tensor<T> matmul(tensor2d<T> lhs, tensor2d<T> rhs){
        auto t = make_tensor<T>(static_cast<DMatrix<T>>(
            lhs->data() * rhs->data()
        ), lhs->computeGrad | rhs->computeGrad);

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
                        output_grad->data() * rhs->data().transpose()
                    ));
                }
                if (rhs->computeGrad){
                    rhs_grad = make_tensor<T>(static_cast<DMatrix<T>>(
                        // TODO:  Check to see if order is correct
                        lhs->data().transpose() * output_grad->data()
                    ));
                }

                return {lhs_grad, rhs_grad};
            });
        }

        return t;
    }

    template<typename T>
    tensor<T> multiply(tensor<T> lhs, tensor<T> rhs){
        if (lhs->getType() == rhs->getType()){
            switch(lhs->getType()){
                case TensorType::MATRIX:
                    return matmul(std::static_pointer_cast<Tensor2D<T>>(lhs),
                                  std::static_pointer_cast<Tensor2D<T>>(rhs));
                default:
                    break;
            }
        }
        // else {
        //     switch(lhs->getType()){
        //         default:
        //             break
        //     }
        // }
        throw UnsupportedOperationException("Multiplication:  " + type_name<decltype(lhs)>() + " += " + type_name<decltype(rhs)>());
    }


}

#endif // __CML_FUNCTIONS_TENSOROPS_TENSOR_MULTIPLICATION_H__
