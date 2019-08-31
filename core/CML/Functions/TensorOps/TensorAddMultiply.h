#ifndef __CML_FUNCTIONS_TENSOROPS_TENSORADDMULTIPLY_H__
#define __CML_FUNCTIONS_TENSOROPS_TENSORADDMULTIPLY_H__

#include "TensorOps.h"

namespace cml {

    /*
        Returns t1+(t2*t3)  
     */
    template<typename T>
    tensor<T> addmatmul(tensor<T> t1, tensor<T> t2, tensor<T> t3){
        auto t = make_tensor_from<T>(static_cast<DMatrix<T>>(
            (t2->matrix() * t3->matrix()).colwise() + t1->matrix().col(0)
        ), t1->computeGrad || t2->computeGrad || t3->computeGrad);

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
#ifdef DEBUG
                cout << "    t1: " << t1->rows() << ", " << t1->cols() << "   computeGrad: " << t1->computeGrad << endl;
                cout << "    t2: " << t2->rows() << ", " << t2->cols() << "   computeGrad: " << t2->computeGrad << endl;
                cout << "    t3: " << t3->rows() << ", " << t3->cols() << "   computeGrad: " << t3->computeGrad << endl;
                cout << "    output_grad: " << output_grad->rows() << ", " << output_grad->cols() << endl;
#endif

                if (t3->computeGrad){
                    t3_grad = make_tensor_from<T>(static_cast<DMatrix<T>>(
                        // TODO:  Check to see if order is correct
                        t2->matrix().transpose() * output_grad->matrix()
                    ));
                }
                if (t2->computeGrad){
                    t2_grad = make_tensor_from<T>(static_cast<DMatrix<T>>(
                        // TODO:  Check to see if order is correct
                        t3->matrix() * output_grad->matrix().transpose()
                    ));
                }
                if (t1->computeGrad){
                    t1_grad = make_tensor_from<T>(static_cast<DMatrix<T>>(
                        output_grad->matrix().rowwise().sum()
                    ));
                }

#ifdef DEBUG
                if (t1->computeGrad){
                    cout << "    t1_grad: " << t1_grad->rows() << ", " << t1_grad->cols() << endl;
                }
                if (t2->computeGrad){
                    cout << "    t2_grad: " << t2_grad->rows() << ", " << t2_grad->cols() << endl;
                }
                if (t3->computeGrad){
                    cout << "    t3_grad: " << t3_grad->rows() << ", " << t3_grad->cols() << endl;
                }
#endif

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
//         if (t1->getType() == t2->getType() && t1->getType() == t3->getType()){
//             switch(t1->getType()){
//                 case TensorType::MATRIX:
//                     return addmatmul(std::static_pointer_cast<Tensor2D<T>>(t1),
//                                      std::static_pointer_cast<Tensor2D<T>>(t2),
//                                      std::static_pointer_cast<Tensor2D<T>>(t3));
//                 default:
//                     break;
//             }
//         }
        // else {
        //     switch(lhs->getType()){
        //         default:
        //             break
        //     }
        // }
//         throw UnsupportedOperationException("Add Multiply:  " + type_name<decltype(t1)>() + " + " + type_name<decltype(t2)>() + " * " + type_name<decltype(t3)>());
        
        // TODO: Make this more general, i.e. Eigen::Tensor Contractions
        return addmatmul(t1, t2, t3);
    }

}

#endif // __CML_FUNCTIONS_TENSOROPS_TENSORADDMULTIPLY_H__
