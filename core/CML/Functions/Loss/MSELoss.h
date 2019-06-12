#ifndef __CML_FUNCTIONS_LOSS_MEANSQUARED_H__
#define __CML_FUNCTIONS_LOSS_MEANSQUARED_H__

#include "../../Tensor.h"
#include "../../DCG.h"
#include "../../Dtypes.h"

namespace cml {
namespace Function {
    
    struct MSELoss {
        
        template<typename T>
        static tensor<T> forward(tensor<T> actual, tensor<T> expected, const nn::Reduction& reduction = nn::Reduction::MEAN){
            tensor<T> t = nullptr;
            switch(reduction){
                case nn::Reduction::MEAN:
                    t = make_tensor<T>(static_cast<DMatrix<T>>(
                        (actual->data() - expected->data()).array().square().rowwise().mean()
                    ));
                    break;
                case nn::Reduction::SUM:
                    t = make_tensor<T>(static_cast<DMatrix<T>>(
                        (actual->data() - expected->data()).array().square().rowwise().sum()
                    ));
                    break;
                default:
                    t = make_tensor<T>(static_cast<DMatrix<T>>(
                        (actual->data() - expected->data()).array().square()
                    ));
                    break;
            }
            t->computeGrad = true;
            t->initGraph([actual, expected, reduction](tensor<T> output) -> tensor<T> {
                std::cout << "MSELoss.actual:" << std::endl << actual << std::endl;
                std::cout << "MSELoss.expected:" << std::endl << expected << std::endl;
                auto u = make_tensor<T>(static_cast<DMatrix<T>>(
                    2*(actual->data() - expected->data())
                ));
                std::cout << "MSELoss.u:" << std::endl << u << std::endl;
                return u;
            });
            return t;
        }

    };

    template<typename T>
    inline tensor<T> MSELoss(tensor<T> actual, tensor<T> expected, const nn::Reduction& reduction = nn::Reduction::MEAN){
        return MSELoss::forward(actual, expected, reduction);
    }

};
};

#endif // __CML_FUNCTIONS_LOSS_MEANSQUARED_H__
