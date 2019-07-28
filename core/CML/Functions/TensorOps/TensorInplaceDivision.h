#ifndef __CML_FUNCTIONS_TENSOROPS_TENSORINPLACEDIVISION_H__
#define __CML_FUNCTIONS_TENSOROPS_TENSORINPLACEDIVISION_H__

#include "TensorOps.h"

namespace cml {

    template<typename T, typename U>
    inline tensor<T> inplaceDivision(tensor2d<T> t, const U& scalar){
        t->data() /= scalar;
        return t;
    }

    template<typename T, typename U>
    tensor<T> inplaceDivision(tensor<T> t, const U& scalar){
        switch(t->getType()){
            case TensorType::MATRIX:
                return inplaceDivision(std::static_pointer_cast<Tensor2D<T>>(t), scalar);
            default:
                throw UnsupportedOperationException("Inplace Division:  " + type_name<decltype(t)>() + " /= " + type_name<decltype(scalar)>());
        }
    }

}

#endif // __CML_FUNCTIONS_TENSOROPS_TENSORINPLACEDIVISION_H__
