#ifndef __CML_OPTIM_OPTIMIZERS_OPTIMIZER_H__
#define __CML_OPTIM_OPTIMIZERS_OPTIMIZER_H__

#include "../../Tensor.h"
#include "../../nn/Modules.h"

namespace cml {
namespace optim {
    
    template<typename T>
    struct Optimizer {
        virtual void step() = 0;
        protected:
            nn::Parameters<T> params;
            Optimizer(nn::Parameters<T>& params):  params {std::move(params)} {}
            Optimizer(nn::Parameters<T>&& params): params {std::move(params)} {}
        
        public:
            void zeroGrad(){
                for (auto& param : params){
                    param->gradient()->zero();
                }
            }
    };    
    
}
}

#endif // __CML_OPTIM_OPTIMIZERS_OPTIMIZER_H__
