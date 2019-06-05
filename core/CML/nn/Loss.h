#ifndef __CML_NN_LOSS_H__
#define __CML_NN_LOSS_H__

#include "Modules.h"
#include "Parameter.h"
#include "../Tensor.h"

namespace cml {
namespace nn {

    enum Reduction {
        NONE,
        SUM,
        MEAN
    };

    template<typename T = float>
    struct Criterion {
        virtual cml::tensor<T> forward(cml::tensor<T> actual, cml::tensor<T> expected) = 0;
        virtual cml::tensor<T> backward() = 0;
    };

    template<typename T = float>
    class MSELoss: public Criterion<T> {
        /*
        Creates a criterion that measures the mean squared error (squared L2 norm) 
        between each element in the input x and target y.

        The unreduced (i.e. with reduction set to Reduction::NONE) loss can be described as:
        
            l(x, y) = L = {l_1, l_2, ..., l_N}^T,  l_n = (x_n - y_n)^2

        where N is the batch size. If reduction is not Reduction::NONE (default Reduction::MEAN), then:

            l(x, y) = {
                sum(L):     If reduction == Reduction::SUM
                mean(L):    If reduction == Reduction::MEAN
            }
        
        Params:
            reduction - The Reduction operation to be applied. Default: Reduction::MEAN
        */
        Reduction reduction;
        
        public:
            ReLU(const Reduction& reduction = Reduction::MEAN);

            cml::tensor<T> forward(cml::tensor<T> actual, cml::tensor<T> expected) override;
            cml::tensor<T> backward() override;
    };

}
}


#endif // __CML_NN_LOSS_H__
