#ifndef __CML_FUNCTIONS_LOSS_LOSS_H__
#define __CML_FUNCTIONS_LOSS_LOSS_H__

namespace cml {

    template<typename T, int nDims> class Tensor;

    namespace Function {

        template<typename T>
        tensor<T> MSELoss(tensor<T> actual, tensor<T> expected, const nn::Reduction& reduction = nn::Reduction::MEAN);
        template<typename T, int nDims>
        tensor<T> MSELoss(Tensor<T, nDims>* actual, Tensor<T, nDims>* expected, const nn::Reduction& reduction = nn::Reduction::MEAN);

        template<typename T>
        tensor<T> CrossEntropyLoss(tensor<T> actual, tensor<T> expected);
        template<typename T, int nDims>
        tensor<T> CrossEntropyLoss(Tensor<T, nDims>* actual, Tensor<T, nDims>* expected);

    }

}

#endif // __CML_FUNCTIONS_LOSS_LOSS_H__
