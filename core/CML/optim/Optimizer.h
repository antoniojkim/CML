#ifndef __CML_OPTIM_OPTIMIZER_H__
#define __CML_OPTIM_OPTIMIZER_H__

#include <map>
#include <memory>
#include <string>

#include "Optimizers/SGD.h"
#include "../Dtypes.h"
#include "../nn/Modules.h"

namespace cml {
    
    enum Optimizers {
        SGD
    };

    std::map<std::string, Optimizers> OptimizerMap {
        {"SGD", Optimizers::SGD}
    };

    template<typename T>
    std::unique_ptr<optim::Optimizer<T>> make_optimizer(const std::string& optimizer, nn::Module<T>& model, Kwargs kwargs) {
        if (!OptimizerMap.count(optimizer)){
            throw "Invalid Optimizer Provided: " + optimizer;
        }

        switch(OptimizerMap[optimizer]){
            case Optimizers::SGD:
                return std::make_unique<optim::SGD<T>>(model.parameters(), std::forward<Kwargs>(kwargs));
            default:
                throw "Invalid Optimizer Provided: " + optimizer;
        }
    }
    
}

#endif // __CML_OPTIM_OPTIMIZER_H__
