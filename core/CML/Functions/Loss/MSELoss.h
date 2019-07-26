#ifndef __CML_FUNCTIONS_LOSS_MEANSQUARED_H__
#define __CML_FUNCTIONS_LOSS_MEANSQUARED_H__

#include "../../Tensor.h"
#include "../../Dtypes.h"

namespace cml {
namespace Function {
    
    struct MSELoss {
        
        template<typename T>
        static tensor<T> forward(tensor2d<T> actual, tensor2d<T> expected, const nn::Reduction& reduction = nn::Reduction::MEAN){
            tensor<T> t = nullptr;
            switch(reduction){
                case nn::Reduction::MEAN:
                    t = make_tensor<T>(static_cast<DMatrix<T>>(
                        (actual->data() - expected->data()).array().square().colwise().mean()
                    ));
                    break;
                case nn::Reduction::SUM:
                    t = make_tensor<T>(static_cast<DMatrix<T>>(
                        (actual->data() - expected->data()).array().square().colwise().sum()
                    ));
                    break;
                default:
                    t = make_tensor<T>(static_cast<DMatrix<T>>(
                        (actual->data() - expected->data()).array().square()
                    ));
                    break;
            }
            t->computeGrad = true;
            t->initGraph({actual, expected}, [reduction](std::vector<tensor<T>>& params, std::vector<tensor<T>> output) -> std::vector<tensor<T>> {
#ifdef DEBUG
                using namespace std;
                cout << "MSELoss::backward()" << endl;
#endif
                auto actual = params.at(0);
                auto expected = params.at(1);

                T c = 0;
                switch(reduction){
                    case nn::Reduction::MEAN:
                        c = (T)(2.0/actual->data()->size());
                        break;
                    case nn::Reduction::SUM:
                        c = (T)(2);
                        break;
                    default:
                        c = (T)(2);
                        break;
                }

                tensor<T> actual_grad = make_tensor<T>(static_cast<DMatrix<T>>(
                    c*(actual->data() - expected->data())
                ));

                return {actual_grad, nullptr};
            });
            return t;
        }
        

        template<typename T>
        static tensor<T> forward(tensor<T> actual, tensor<T> expected, const nn::Reduction& reduction = nn::Reduction::MEAN){
            if (actual->getType() != expected->getType()){
                throw TensorTypeMismatchException();
            }

            switch(actual->getType()){
                case TensorType::MATRIX:
                    return forward(std::static_pointer_cast<Tensor2D<T>>(actual),
                                   std::static_pointer_cast<Tensor2D<T>>(expected),
                                   reduction);
                default:
                    throw UnsupportedOperationException("MSELoss unsupported for Tensor type");
            }
        }

    };

    template<typename T>
    inline tensor<T> MSELoss(tensor<T> actual, tensor<T> expected, const nn::Reduction& reduction = nn::Reduction::MEAN){
        return MSELoss::forward(actual, expected, reduction);
    }

}
}

#endif // __CML_FUNCTIONS_LOSS_MEANSQUARED_H__
