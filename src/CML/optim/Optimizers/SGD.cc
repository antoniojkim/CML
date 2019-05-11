
#include <sstream>

#include "../Optimizer.h"

using namespace std;
using namespace cml::nn;
using namespace cml::optim;


SGD::SGD(Parameters* params,
         const double& lr, 
         const double& momentum, 
         const double& weight_decay,
         const double& dampening,
         const bool& nesterov):
    Optimizer {params},
    lr {lr}, momentum {momentum}, 
    weight_decay {weight_decay}, dampening {dampening}, nesterov {nesterov} {
        
    ostringstream error;
    if (lr < 0){
        error << "Invalid Learning Rate:  " << lr;
        throw error.str();
    }
    if (momentum < 0){
        error << "Invalid Momentum value:  " << momentum;
        throw error.str();
    }
    if (weight_decay < 0){
        error << "Invalid weight_decay value:  " << momentum;
        throw error.str();
    }
    if (nesterov && (momentum <= 0 || dampening != 0)){
        error << "Nesterov momentum requires a momentum and zero dampening";
        throw error.str();
    }
}

void SGD::step(){
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