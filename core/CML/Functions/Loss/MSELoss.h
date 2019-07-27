#ifndef __CML_FUNCTIONS_LOSS_MEANSQUARED_H__
#define __CML_FUNCTIONS_LOSS_MEANSQUARED_H__

#include "../../Tensor.h"
#include "../../Dtypes.h"

namespace cml {
namespace Function {

    template <typename T, typename ActualType, typename ExpectedType>
    using MSEMeanReturnType = Eigen::PartialReduxExpr<
        Eigen::CwiseUnaryOp<
            Eigen::internal::scalar_square_op<T>,
            Eigen::ArrayWrapper<Eigen::CwiseBinaryOp<Eigen::internal::scalar_difference_op<T, T>, ActualType const,
                                                    ExpectedType const> const> const> const,
        Eigen::internal::member_mean<T>, 0> const;


    template <typename T, typename ActualType, typename ExpectedType>
    using MSESumReturnType = Eigen::PartialReduxExpr<
        Eigen::CwiseUnaryOp<
            Eigen::internal::scalar_square_op<T>,
            Eigen::ArrayWrapper<Eigen::CwiseBinaryOp<Eigen::internal::scalar_difference_op<T, T>, ActualType const,
                                                    ExpectedType const> const> const> const,
        Eigen::internal::member_sum<T>, 0> const;


    template <typename T, typename ActualType, typename ExpectedType>
    using MSEReturnType = Eigen::CwiseUnaryOp<Eigen::internal::scalar_square_op<T>,
        Eigen::ArrayWrapper<Eigen::CwiseBinaryOp<Eigen::internal::scalar_difference_op<T, T>,
                                                    ActualType const, ExpectedType const> const> const> const

    template <typename T>
    using MSEGradientReturnType = Eigen::CwiseBinaryOp<
        Eigen::internal::scalar_product_op<T, T>,
        Eigen::CwiseNullaryOp<Eigen::internal::scalar_constant_op<T>, DMatrix<T> const> const,
        Eigen::CwiseBinaryOp<Eigen::internal::scalar_difference_op<T, T>, DMatrix<T> const, DMatrix<T> const> const> const


    struct MSELoss {
        
        template<typename T>
        static tensor<T> forward(tensor2d<T> actual, tensor2d<T> expected, const nn::Reduction& reduction = nn::Reduction::MEAN){
            tensor<T> t = nullptr;
            switch(reduction){
                case nn::Reduction::MEAN:
                    t = make_tensor<T, MSEMeanReturnType<T, decltype(actual->data()), decltype(expected->data())>>(
                        (actual->data() - expected->data()).array().square().colwise().mean()
                    );
                    break;
                case nn::Reduction::SUM:
                    t = make_tensor<T, MSESumReturnType<T, decltype(actual->data()), decltype(expected->data())>>(
                        (actual->data() - expected->data()).array().square().colwise().sum()
                    );
                    break;
                default:
                    t = make_tensor<T, MSEReturnType<T, decltype(actual->data()), decltype(expected->data())>>(
                        (actual->data() - expected->data()).array().square()
                    );
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
                        c = (T)(2.0/actual->data().size());
                        break;
                    case nn::Reduction::SUM:
                        c = (T)(2);
                        break;
                    default:
                        c = (T)(2);
                        break;
                }

                tensor<T> actual_grad = make_tensor<T, MSEGradientReturnType<T, decltype(actual->data()), decltype(expected->data())>>(
                    c*(actual->data() - expected->data())
                );

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
