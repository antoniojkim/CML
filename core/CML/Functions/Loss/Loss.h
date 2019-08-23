#ifndef __CML_FUNCTIONS_LOSS_LOSS_H__
#define __CML_FUNCTIONS_LOSS_LOSS_H__

#include "../../Tensors/TensorDecl.h"
#include "../../Dtypes.h"

namespace cml {

    namespace Function {

        template<typename T>
        tensor<T> MSELoss(tensor<T> actual, tensor<T> expected, const nn::Reduction& reduction = nn::Reduction::MEAN);

        template<typename T>
        tensor<T> CrossEntropyLoss(tensor<T> actual, tensor<T> expected);

    }

}

#endif // __CML_FUNCTIONS_LOSS_LOSS_H__
