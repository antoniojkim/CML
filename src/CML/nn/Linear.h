#ifndef __CML_NN_LINEAR_H__
#define __CML_NN_LINEAR_H__

#include "Modules.h"
#include "../Tensor.h"

namespace cml {
namespace nn {


    class Linear: public Module {
        int in_features, out_features;
        bool bias;

        public:
            Linear(const int& in_features, const int& out_features, const bool& bias = true);

            Parameter getWeights();
            Parameter getBias();

            std::ostream& print(std::ostream&, const std::string& indent);

    };

    typedef 

}
}


#endif // __CML_NN_LINEAR_H__
