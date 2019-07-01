
#ifndef __CML_NN_LINEAR_LINEAR_H__
#define __CML_NN_LINEAR_LINEAR_H__

#include "../Modules.h"
#include "../../Tensor.h"
#include "../../Functions/Linear.h"

namespace cml {
namespace nn {

    template<typename T = float>
    class Linear: public Module<T> {
        /*
        The weights are stored in the module's parameters under the alias "weights"
        The bias is stored in the module's parameters under the alias "bias"
        */

        using Module<T>::params;
        using Module<T>::addParameter;
        
        int in_features, out_features;
        bool bias;

        public:
            Linear(const int& in_features, const int& out_features, const bool& bias = true): 
                in_features{in_features}, out_features{out_features}, bias{bias} {
                addParameter("weights", in_features, out_features, true);
                if (bias) addParameter("bias", out_features, 1, true);

                // Initialize Weights to random
                params[0]->randomize();
                if (bias) params[1]->randomize();
            }   

            Parameter<T>& getWeights(){ return params[0]; }
            Parameter<T>& getBias(){
                if (bias) return params[1];
                throw "Attempting to get bias from Linear layer without bias";
            }

            cml::tensor<T> forward(cml::tensor<T> x) override {
                return bias ? Function::Linear::forward(x, getWeights(), getBias()) :
                              Function::Linear::forward(x, getWeights());
            }

            std::ostream& print(std::ostream& out, const std::string& indent) override {
                return out << "Linear { in_features: " << in_features << 
                                    "  out_features: " << out_features << "  bias: " << (bias ? "true" : "false") << " }";
            }

    };

}
}


#endif // __CML_NN_LINEAR_LINEAR_H__
