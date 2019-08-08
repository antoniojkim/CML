#ifndef __CML_OPTIM_OPTIMIZERS_OPTIMIZER_H__
#define __CML_OPTIM_OPTIMIZERS_OPTIMIZER_H__

#include <iostream>
#include <string>

#include "../../Tensor.h"
#include "../../nn/Modules.h"

namespace cml {
namespace optim {
    
    template<typename T>
    struct Optimizer {
        protected:
            Parameters<T> params;
            Optimizer(Parameters<T>& params):  params {std::move(params)} {}
            Optimizer(Parameters<T>&& params): params {std::move(params)} {}
        
        public:
            void zeroGrad(){
                for (auto& param : params){
                    param->gradient()->zero();
                }
            }
        
            virtual void step() = 0;
            virtual std::ostream& print(std::ostream& out, const std::string& indent = "") = 0;
    };    
    
}
}

#endif // __CML_OPTIM_OPTIMIZERS_OPTIMIZER_H__
