#ifndef __CML_OPTIM_OPTIMIZERS_SGD_H__
#define __CML_OPTIM_OPTIMIZERS_SGD_H__

#include <vector>

#include "Optimizer.h"

namespace cml {
namespace optim {
    
    template<typename T>
    class SGD: public Optimizer<T> {
        double lr = 0.01; // learning Rate
        double momentum = 0; // momentum factor
        double weight_decay = 0; // weight decay (L2 penalty)
        double dampening = 0; // dampening for momentum
        bool nesterov = false; // enables Nesterov momentum
        
        /*
                const double& lr = 0.01, 
                const double& momentum = 0, 
                const double& weight_decay = 0,
                const double& dampening = 0,
                const bool& nesterov = false
        */
    
        public:
            SGD(nn::Parameters<T>&& params, Kwargs kwargs): Optimizer<T>{params} {
                
                if (kwargs.count("lr")){
                    lr = kwargs["lr"];
                }
                if (kwargs.count("momentum")){
                    momentum = kwargs["momentum"];
                }
                if (kwargs.count("weight_decay")){
                    weight_decay = kwargs["weight_decay"];
                }
                if (kwargs.count("dampening")){
                    dampening = kwargs["dampening"];
                }
                if (kwargs.count("nesterov")){
                    nesterov = (bool)kwargs["nesterov"];
                }
        
                std::ostringstream error;
                if (lr < 0){
                    error << "Invalid Learning Rate:  " << lr;
                    throw error.str();
                }
                if (momentum < 0){
                    error << "Invalid Momentum value:  " << momentum;
                    throw error.str();
                }
                if (weight_decay < 0){
                    error << "Invalid weight_decay value:  " << weight_decay;
                    throw error.str();
                }
                if (nesterov && (momentum <= 0 || dampening != 0)){
                    error << "Nesterov momentum requires a momentum and zero dampening";
                    throw error.str();
                }
            }
                
            void step() override {
                /*
                def step(self, closure=None):
                    """Performs a single optimization step.

                    Arguments:
                        closure (callable, optional): A closure that reevaluates the model
                            and returns the loss.
                    """
                    loss = None
                    if closure is not None:
                        loss = closure()

                    for group in self.param_groups:
                        weight_decay = group['weight_decay']
                        momentum = group['momentum']
                        dampening = group['dampening']
                        nesterov = group['nesterov']

                        for p in group['params']:
                            if p.grad is None:
                                continue
                            d_p = p.grad.data
                            if weight_decay != 0:
                                d_p.add_(weight_decay, p.data)
                            if momentum != 0:
                                param_state = self.state[p]
                                if 'momentum_buffer' not in param_state:
                                    buf = param_state['momentum_buffer'] = torch.clone(d_p).detach()
                                else:
                                    buf = param_state['momentum_buffer']
                                    buf.mul_(momentum).add_(1 - dampening, d_p)
                                if nesterov:
                                    d_p = d_p.add(momentum, buf)
                                else:
                                    d_p = buf

                            p.data.add_(-group['lr'], d_p)

                    return loss
                */
            }
    };
    
}
}

#endif // __CML_OPTIM_OPTIMIZERS_SGD_H__
