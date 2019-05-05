#ifndef __CML_NN_PARAMETER_H__
#define __CML_NN_PARAMETER_H__

#include "../Tensor.h"

namespace cml {
namespace nn {

    template <class T>
    struct __Parameter__ {
        __Tensor__<T> data;
        bool requires_grad = true;
    };
    
    typedef __Parameter__<float> Parameter;
    typedef __Parameter__<double> ParameterD;
    
}
}

#endif // __CML_NN_PARAMETER_H__
