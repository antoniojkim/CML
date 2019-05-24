#ifndef __CML_NN_LINEAR_H__
#define __CML_NN_LINEAR_H__

#include "Modules.h"
#include "Parameter.h"
#include "../Tensor.h"

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
            Linear(const int& in_features, const int& out_features, const bool& bias = true);

            Parameter<T>& getWeights();
            Parameter<T>& getBias();

            cml::Tensor<T> forward(const cml::Tensor<T>&) override;

            std::ostream& print(std::ostream&, const std::string& indent) override;

    };

}
}


#endif // __CML_NN_LINEAR_H__
