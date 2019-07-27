#ifndef __CML_FUNCTIONS_TENSOROPS_DECREMENT_H__
#define __CML_FUNCTIONS_TENSOROPS_DECREMENT_H__

#include "TensorOps.h"

namespace cml {

    template<typename T>
    inline tensor<T> decrement(tensor2d<T> lhs, tensor2d<T> rhs){
        lhs->data() += rhs->data();
        return lhs;
    }
    
    template<typename T>
    tensor<T> decrement(tensor<T> lhs, tensor<T> rhs){
        if (lhs->getType() == rhs->getType()){
            switch(lhs->getType()){
                case TensorType::MATRIX:
                    return decrement(std::static_pointer_cast<Tensor2D<T>>(lhs),
                                     std::static_pointer_cast<Tensor2D<T>>(rhs));
                default:
                    break;
            }
        }
        // else {
        //     switch(lhs->getType()){
        //         default:
        //             break
        //     }
        // }
        throw UnsupportedOperationException("Decrement:  " + type_name<decltype(lhs)>() + " -= " + type_name<decltype(rhs)>());
    }


}

#endif // __CML_FUNCTIONS_TENSOROPS_DECREMENT_H__