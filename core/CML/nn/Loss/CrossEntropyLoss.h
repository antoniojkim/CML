#ifndef __CML_NN_LOSS_CROSSENTROPYLOSS_H__
#define __CML_NN_LOSS_CROSSENTROPYLOSS_H__
#include "../../Dtypes.h"
#include "../../Functions/Loss/CrossEntropyLoss.h"
#include "../../Tensors/Tensor2D.h"
#include "Criterion.h"

namespace cml {
namespace nn {


    template<typename T = float>
    class CrossEntropyLoss: public Criterion<T> {
        
        public:
            CrossEntropyLoss() {}

            cml::tensor<T> forward(cml::tensor<T> actual, cml::tensor<T> expected) override {
                return Function::CrossEntropyLoss::forward(actual, expected);
            }
    };

}
}


#endif // __CML_NN_LOSS_CROSSENTROPYLOSS_H__
