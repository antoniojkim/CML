#ifndef __CML_OPTIM_OPTIMIZERS_SGD_H__
#define __CML_OPTIM_OPTIMIZERS_SGD_H__

#include <vector>

#include "Optimizer.h"

namespace cml {
namespace optim {
    
    template<typename T>
    class SGD: public Optimizer<T> {
        using Optimizer<T>::params;
        
        double lr = 0.01; // learning Rate
        double momentum = 0; // momentum factor
        double weight_decay = 0; // weight decay (L2 penalty)
        double dampening = 0; // dampening for momentum
        bool nesterov = false; // enables Nesterov momentum
    
        public:
            SGD(Parameters<T>&& params, Kwargs kwargs = {}): Optimizer<T>{params} {
                
                if (kwargs.count("lr")){ lr = kwargs["lr"]; }
                if (kwargs.count("learning_rate")){ lr = kwargs["learning_rate"]; }
                if (kwargs.count("learningRate")){ lr = kwargs["learningRate"]; }
                
                if (kwargs.count("momentum")){ momentum = kwargs["momentum"]; }
                if (kwargs.count("weight_decay")){ weight_decay = kwargs["weight_decay"]; }
                if (kwargs.count("dampening")){ dampening = kwargs["dampening"]; }
                if (kwargs.count("nesterov")){ nesterov = (bool)kwargs["nesterov"]; }
        
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
                for (auto& param : params){
                    if (param->computeGrad){
                        param->data() -= lr * param->gradient()->data();
                    }
                }
            }
        
        
            std::ostream& print(std::ostream& out, const std::string& indent) override {
                using namespace std;
                out << indent << "SGD:" << endl;
                out << indent << "    lr:           " << lr << endl;
                out << indent << "    momentum:     " << momentum << endl;
                out << indent << "    weight_decay: " << weight_decay << endl;
                out << indent << "    dampening:    " << dampening << endl;
                out << indent << "    nesterov:     " << nesterov << endl;
                return out;
            }
    };
    
}
}

#endif // __CML_OPTIM_OPTIMIZERS_SGD_H__
