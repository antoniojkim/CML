#ifndef __CML_FUNCTIONS_LOSS_MEANSQUARED_H__
#define __CML_FUNCTIONS_LOSS_MEANSQUARED_H__

#include "../../Tensors/Tensor.h"
#include "../../Dtypes.h"

namespace cml {
namespace Function {
    
    struct MSELoss {

        template<typename T, int nDims>
        static std::vector<tensor<T>> mean_backward(std::vector<tensor<T>>& params, std::vector<tensor<T>> output) {
            auto actual = CAST_TENSOR_NDIMS(params.at(0));
            auto expected = CAST_TENSOR_NDIMS(params.at(1));

            T c = (T)(2.0/actual->tensor().size());

            tensor<T> actual_grad = make_tensor<T>(CAST_EIGEN_TENSOR(
                c*(actual->tensor() - expected->tensor())
            ));

            return {actual_grad, nullptr};
        }

        template<typename T, int nDims>
        static std::vector<tensor<T>> sum_backward(std::vector<tensor<T>>& params, std::vector<tensor<T>> output) {
            auto actual = CAST_TENSOR_NDIMS(params.at(0));
            auto expected = CAST_TENSOR_NDIMS(params.at(1));
            
            T c = (T)(2);

            tensor<T> actual_grad = make_tensor<T>(CAST_EIGEN_TENSOR(
                c*(actual->tensor() - expected->tensor())
            ));

            return {actual_grad, nullptr};
        }

        template<typename T, int nDims>
        static std::vector<tensor<T>> backward(std::vector<tensor<T>>& params, std::vector<tensor<T>> output) {
            auto actual = CAST_TENSOR_NDIMS(params.at(0));
            auto expected = CAST_TENSOR_NDIMS(params.at(1));
            
            T c = (T)(2);

            tensor<T> actual_grad = make_tensor<T>(CAST_EIGEN_TENSOR(
                c*(actual->tensor() - expected->tensor())
            ));

            return {actual_grad, nullptr};
        }
        
        template<typename T, int nDims>
        static tensor<T> forward(tensor<T> actual, tensor<T> expected, const nn::Reduction& reduction = nn::Reduction::MEAN){
            tensor<T> t = nullptr;
            GradientFunction<T> gradient = nullptr;
            switch(reduction){
                case nn::Reduction::MEAN:
                    t = make_tensor<T>(CAST_EIGEN_TENSOR(
                        (actual->tensor() - expected->tensor()).square().mean(Eigen::array<int, 1>({actual->numDims()-1}))
                    ));
                    gradient = &mean_backward<T, nDims>;
                    break;
                case nn::Reduction::SUM:
                    t = make_tensor<T>(CAST_EIGEN_TENSOR(
                        (actual->tensor() - expected->tensor()).square().sum(Eigen::array<int, 1>({actual->numDims()-1}))
                    ));
                    gradient = &sum_backward<T, nDims>;
                    break;
                default:
                    t = make_tensor<T>(CAST_EIGEN_TENSOR(
                        (actual->tensor() - expected->tensor()).square()
                    ));
                    gradient = &backward<T, nDims>;
                    break;
            }
            t->computeGrad = true;
            t->initGraph({actual, expected}, gradient);
            return t;
        }

    };

    template<typename T>
    inline tensor<T> MSELoss(tensor<T> actual, tensor<T> expected, const nn::Reduction& reduction){
        return actual->MSELoss(expected, reduction);
    }
    template<typename T, int nDims>
    inline tensor<T> MSELoss(tensor<T> actual, tensor<T> expected, const nn::Reduction& reduction){
        return MSELoss::forward(actual, expected, reduction);
    }



}
}

#endif // __CML_FUNCTIONS_LOSS_MEANSQUARED_H__
