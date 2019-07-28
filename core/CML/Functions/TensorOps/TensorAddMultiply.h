#ifndef __CML_FUNCTIONS_TENSOROPS_TENSORADDMULTIPLY_H__
#define __CML_FUNCTIONS_TENSOROPS_TENSORADDMULTIPLY_H__

#include "TensorOps.h"

namespace cml {

    /*
        Returns t1+(t2*t3)  
     */
    template<typename T>
    tensor<T> addmatmul(tensor2d<T> t1, tensor2d<T> t2, tensor2d<T> t3){
        auto t = make_tensor<T>(static_cast<DMatrix<T>>(
            t1->data().col(0) + (t2->data() * t3->data()).colwise()
        ), t1->computeGrad, t2->computeGrad, t3->computeGrad);

        if (t->computeGrad){
            t->initGraph({t1, t2, t3}, [](std::vector<tensor<T>>& params, std::vector<tensor<T>> output) -> std::vector<tensor<T>> {
#ifdef DEBUG
                using namespace std;
                cout << "Tensor2D Add Multiply Backward" << endl;
#endif
                tensor<T> t1 = params.at(0);
                tensor<T> t2 = params.at(1);
                tensor<T> t3 = params.at(2);
                tensor<T> output_grad = output.at(0);
                tensor<T> t1_grad = nullptr;
                tensor<T> t2_grad = nullptr;
                tensor<T> t3_grad = nullptr;

                if (t2->computeGrad){
                    t2_grad = make_tensor<T>(static_cast<DMatrix<T>>(
                        // TODO:  Check to see if order is correct
                        output_grad->data() * t3->data().transpose()
                    ));
                }
                if (t3->computeGrad){
                    t3_grad = make_tensor<T>(static_cast<DMatrix<T>>(
                        // TODO:  Check to see if order is correct
                        output_grad->data().transpose() * t2->data()
                    ));
                }
                if (t1->computeGrad){
                    t1_grad = make_tensor<T>(static_cast<DMatrix<T>>(
                        output_grad->data().rowwise().sum()
                    ));
                }

                return {t1_grad, t2_grad, t3_grad};
            });
        }

        return t;
    }

    /*
        Returns t1+(t2*t3)
     */
    template<typename T>
    tensor<T> addMultiply(tensor<T> t1, tensor<T> t2, tensor<T> t3){
        if (t1->getType() == t2->getType() && t1->getType() == t3->getType()){
            switch(t1->getType()){
                case TensorType::MATRIX:
                    return addmm(std::static_pointer_cast<Tensor2D<T>>(t1),
                                 std::static_pointer_cast<Tensor2D<T>>(t2),
                                 std::static_pointer_cast<Tensor2D<T>>(t3));
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
        throw UnsupportedOperationException("Add Multiply:  " + type_name<decltype(t1)>() + " + " + type_name<decltype(t2)>() + " * " + type_name<decltype(t3)>());
    }

}

#endif // __CML_FUNCTIONS_TENSOROPS_TENSORADDMULTIPLY_H__
