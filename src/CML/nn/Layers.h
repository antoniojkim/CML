#ifndef __CML_NN_LAYERS_H__
#define __CML_NN_LAYERS_H__

#include <map>
#include <string>

#include "Modules.h"
#include "../Tensor.h"

namespace cml {
namespace nn {
    
//     struct Layer {
//         virtual cml::nn::Variable forward(const cml::nn::Variable&) = 0;
//         virtual cml::nn::Variable backpropogation(const cml::nn::Variable&) = 0;
//         virtual void step(const double& learningRate = 0.1){}
        
//         cml::nn::Variable operator()(const cml::nn::Variable& x){
//             return forward(x);
//         }
//     };
 
    class ReLU: public Module {
        /*
        Applies the rectified linear unit function element-wise:
        
        ReLU(x) = max(0, x)
        
        Params:
            inplace - can optionally do the operation in-place. Default: False
        */
        
        bool inplace;
        
        public:
            ReLU(const bool& inplace = false);

            cml::Tensor forward(const cml::Tensor&) override;
//         cml::nn::Variable backpropogation(const cml::nn::Variable&) override;
    };
    
}
}

#endif // __CML_NN_LAYERS_H__
