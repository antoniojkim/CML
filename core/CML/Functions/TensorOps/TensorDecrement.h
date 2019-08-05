#ifndef __CML_FUNCTIONS_TENSOROPS_DECREMENT_H__
#define __CML_FUNCTIONS_TENSOROPS_DECREMENT_H__

#include "TensorOps.h"

namespace cml {

    template<typename T>
    inline tensor<T> decrement(tensor<T> lhs, tensor<T> rhs){
        lhs->matrix() += rhs->matrix();
        return lhs;
    }


}

#endif // __CML_FUNCTIONS_TENSOROPS_DECREMENT_H__