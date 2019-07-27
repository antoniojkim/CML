#ifndef __CML_FUNCTIONS_LOSS_CROSSENTROPY_H__
#define __CML_FUNCTIONS_LOSS_CROSSENTROPY_H__

#include <cmath>

#include "../../Tensors/Tensor2D.h"
#include "../../Dtypes.h"

namespace cml {
namespace Function {
    
    struct CrossEntropyLoss {
        
        template<typename T>
        static tensor<T> forward(tensor2d<T> actual, tensor2d<T> expected){
            if (expected->data().rows() > 1){
                throw "CrossEntropyLoss::forward:  Expected tensor is not scalar";
            }
//             auto p = Softmax<T>(actual);
            
            // This is more stable
            auto p = static_cast<DMatrix<T>>(
                actual->data().rowwise() - static_cast<DMatrix<T>>(actual->data().array().exp().colwise().sum().log()).row(0));
            int m = expected->data().cols();
            T sum_log_likelihood = 0;
            for (int i = 0; i<m; ++i){
                sum_log_likelihood -= p(expected->at(0, i), i);
            }
            tensor<T> t = make_tensor<T>({sum_log_likelihood / m});
            t->computeGrad = true;
            t->initGraph({actual, expected}, [m, p{std::move(p)}](std::vector<tensor<T>>& params, std::vector<tensor<T>> output) mutable -> std::vector<tensor<T>> {
#ifdef DEBUG
                using namespace std;
                cout << "CrossEntropyLoss::backward()" << endl;
#endif
                auto expected = params.at(1);

                p = p.array().exp();
                for (int i = 0; i<m; ++i){
                    p(expected->data(0, i), i) -= 1;
                }
                p /= m;
                tensor<T> actual_grad = make_tensor<T>(p);

                return {actual_grad, nullptr};
            });
            return t;
        }

        template<typename T>
        static tensor<T> forward(tensor<T> actual, tensor<T> expected){
            if (actual->getType() != expected->getType()){
                throw TensorTypeMismatchException();
            }

            switch(actual->getType()){
                case TensorType::MATRIX:
                    return forward(std::static_pointer_cast<Tensor2D<T>>(actual),
                                   std::static_pointer_cast<Tensor2D<T>>(expected));
                default:
                    throw UnsupportedOperationException("CrossEntropyLoss unsupported for Tensor type");
            }
        }

    };

    template<typename T>
    inline tensor<T> CrossEntropyLoss(tensor<T> actual, tensor<T> expected){
        return CrossEntropyLoss::forward(actual, expected);
    }

};
};

#endif // __CML_FUNCTIONS_LOSS_CROSSENTROPY_H__
