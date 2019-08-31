#ifndef __CML_FUNCTIONS_LOSS_MEANSQUARED_H__
#define __CML_FUNCTIONS_LOSS_MEANSQUARED_H__

#include "../../Tensors/Tensor.h"
#include "../../Dtypes.h"

namespace cml {
namespace Function {
    
    struct MSELoss {

        template<typename T>
        static std::vector<tensor<T>> mean_backward(std::vector<tensor<T>>& params, std::vector<tensor<T>> output) {
            auto actual = params.at(0);
            auto expected = params.at(1);

            T c = (T)(2.0/actual->size());

            tensor<T> actual_grad = actual->empty();
            actual_grad->matrix() = c*(actual->matrix() - expected->matrix());

            return {actual_grad, nullptr};
        }

        template<typename T>
        static std::vector<tensor<T>> sum_backward(std::vector<tensor<T>>& params, std::vector<tensor<T>> output) {
            auto actual = params.at(0);
            auto expected = params.at(1);
            
            T c = (T)(2);

            tensor<T> actual_grad = actual->empty();
            actual_grad->matrix() = c*(actual->matrix() - expected->matrix());

            return {actual_grad, nullptr};
        }

        template<typename T>
        static std::vector<tensor<T>> backward(std::vector<tensor<T>>& params, std::vector<tensor<T>> output) {
            auto actual = params.at(0);
            auto expected = params.at(1);
            
            T c = (T)(2);

            tensor<T> actual_grad = actual->empty();
            actual_grad->matrix() = c*(actual->matrix() - expected->matrix());

            return {actual_grad, nullptr};
        }
        
        template<typename T>
        static tensor<T> forward(tensor<T> actual, tensor<T> expected, const nn::Reduction& reduction = nn::Reduction::MEAN){
            tensor<T> t = nullptr;
            GradientFunction<T> gradient = nullptr;
            // TODO:  Make more general to support multidimensional MSELoss
            switch(reduction){
                case nn::Reduction::MEAN:
                    t = make_tensor_from<T>(CAST_MATRIX(
                        (actual->matrix() - expected->matrix()).array().square().colwise().mean()
                    ));
                    gradient = &mean_backward<T>;
                    break;
                case nn::Reduction::SUM:
                    t = make_tensor_from<T>(CAST_MATRIX(
                        (actual->matrix() - expected->matrix()).array().square().colwise().sum()
                    ));
                    gradient = &sum_backward<T>;
                    break;
                default:
                    t = actual->empty();
                    t->matrix() = (actual->matrix() - expected->matrix()).array().square();
                    gradient = &backward<T>;
                    break;
            }
            t->computeGrad = true;
            t->initGraph({actual, expected}, gradient);
            return t;
        }

    };

    template<typename T>
    inline tensor<T> MSELoss(tensor<T> actual, tensor<T> expected, const nn::Reduction& reduction){
        return MSELoss::forward(actual, expected, reduction);
    }



}
}

#endif // __CML_FUNCTIONS_LOSS_MEANSQUARED_H__
