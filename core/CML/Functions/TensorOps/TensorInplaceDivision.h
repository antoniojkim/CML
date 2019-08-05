#ifndef __CML_FUNCTIONS_TENSOROPS_TENSORINPLACEDIVISION_H__
#define __CML_FUNCTIONS_TENSOROPS_TENSORINPLACEDIVISION_H__

#include "TensorOps.h"

namespace cml {

    template<typename T, typename U>
    inline tensor<T> inplaceDivision(tensor<T> t, const U& scalar){
        t->matrix() /= scalar;
        return t;
    }

}

#endif // __CML_FUNCTIONS_TENSOROPS_TENSORINPLACEDIVISION_H__
