#ifndef __CML_NN_OPTIMIZER_H__
#define __CML_NN_OPTIMIZER_H__

#include <vector>

#include "../nn/Parameter.h"

namespace cml {
namespace optim {
    
    struct Optimizer {
        virtual void step() = 0;
        protected:
            std::vector<cml::nn::Parameter> params;
            Optimizer(const std::vector<cml::nn::Parameter>& params): params {params} {}
    };
    
    class SGD: public Optimizer {
        double lr; // learning Rate
        double momentum; // momentum factor
        double weight_decay; // weight decay (L2 penalty)
        double dampening; // dampening for momentum
        bool nesterov; // enables Nesterov momentum
    
        public:
            SGD(const std::vector<cml::nn::Parameter>& params,
                const double& lr, 
                const double& momentum = 0, 
                const double& weight_decay = 0,
                const double& dampening = 0,
                const bool& nesterov = false);
                
            void step() override;
    };
    
}
}

#endif // __CML_NN_OPTIMIZER_H__
