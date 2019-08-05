#ifndef __CML_FUNCTIONS_TENSOROPS_INCREMENT_H__
#define __CML_FUNCTIONS_TENSOROPS_INCREMENT_H__

#include "TensorOps.h"

namespace cml {

    template<typename T>
    inline tensor<T> increment(tensor<T> lhs, tensor<T> rhs){
        lhs->matrix() += rhs->matrix();
        return lhs;
    }


}

#endif // __CML_FUNCTIONS_TENSOROPS_INCREMENT_H__