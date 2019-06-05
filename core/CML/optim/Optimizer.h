#ifndef __CML_NN_OPTIMIZER_H__
#define __CML_NN_OPTIMIZER_H__

#include <vector>

#include "../nn/Parameter.h"

namespace cml {
namespace optim {
    
    template<typename T>
    struct Optimizer {
        virtual void step() = 0;
        protected:
            cml::nn::Parameters<T> params;
            Optimizer(cml::nn::Parameters<T>& params):  params {std::move(params)} {}
            Optimizer(cml::nn::Parameters<T>&& params): params {std::move(params)} {}
    };
    
    template<typename T>
    class SGD: public Optimizer<T> {
        double lr; // learning Rate
        double momentum; // momentum factor
        double weight_decay; // weight decay (L2 penalty)
        double dampening; // dampening for momentum
        bool nesterov; // enables Nesterov momentum
    
        public:
            SGD(cml::nn::Parameters<T>& params,
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
