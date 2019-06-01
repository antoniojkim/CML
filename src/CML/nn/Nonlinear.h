#ifndef __CML_NN_LAYERS_H__
#define __CML_NN_LAYERS_H__

#include <map>
#include <string>

#include "Modules.h"
#include "../Tensor.h"

namespace cml {
namespace nn {
 
    template<typename T = float>
    class ReLU: public Module<T> {
        /*
        Applies the rectified linear unit function element-wise:
        
        ReLU(x) = max(0, x)
        
        Params:
            inplace - can optionally do the operation in-place. Default: False
        */
        
        bool inplace;
        
        public:
            ReLU(const bool& inplace = false);

            cml::Tensor<T> forward(cml::Tensor<T>&) override;

            std::ostream& print(std::ostream&, const std::string& indent) override;
    };
    
}
}

#endif // __CML_NN_LAYERS_H__
