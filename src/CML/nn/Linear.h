#ifndef __CML_NN_LINEAR_H__
#define __CML_NN_LINEAR_H__

#include "Modules.h"
#include "Parameter.h"
#include "../Tensor.h"

namespace cml {
namespace nn {

    class Linear: public Module {
        int in_features, out_features;
        bool bias;

        public:
            Linear(const int& in_features, const int& out_features, const bool& bias = true);

            cml::nn::Parameter getWeights();
            cml::nn::Parameter getBias();

            cml::Tensor forward(const cml::Tensor&) override;

            std::ostream& print(std::ostream&, const std::string& indent) override;

    };

}
}


#endif // __CML_NN_LINEAR_H__
