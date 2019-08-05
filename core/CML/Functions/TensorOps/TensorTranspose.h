#ifndef __CML_FUNCTIONS_TENSOROPS_TENSOR_TRANSPOSE_H__
#define __CML_FUNCTIONS_TENSOROPS_TENSOR_TRANSPOSE_H__

#include "TensorOps.h"

namespace cml {

    // TODO: Make this more general, i.e. Eigen::Tensor contractions
    template<typename T>
    tensor<T> transpose(TensorBase<T>* t){
        auto u = make_tensor<T>(static_cast<DMatrix<T>>(
            t->matrix().transpose()
        ), t->computeGrad);

        if (u->computeGrad){
            u->initGraph({t}, [](std::vector<tensor<T>>& params, std::vector<tensor<T>> output) -> std::vector<tensor<T>> {
#ifdef DEBUG
                using namespace std;
                cout << "Tensor2D Transpose Backward" << endl;
#endif
                auto output_grad = output.at(0);
                // auto t_grad = make_tensor<T>(static_cast<DMatrix<T>>(
                //     output_grad->data().transpose()
                // ));

                return {output_grad};
            });
        }

        return u;
    }

//     template<typename T>
//     tensor<T> transpose(tensor<T> t){
//         switch(t->getType()){
//             case TensorType::MATRIX:
//                 return transpose(std::static_pointer_cast<Tensor2D<T>>(t));
//             default:
//                 break;
//         }
//         throw UnsupportedOperationException("Transpose:  " + type_name<decltype(t)>());
//     }


}

#endif // __CML_FUNCTIONS_TENSOROPS_TENSOR_TRANSPOSE_H__
