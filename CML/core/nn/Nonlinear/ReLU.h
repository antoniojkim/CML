#ifndef __CML_NN_NONLINEAR_RELU_H__
#define __CML_NN_NONLINEAR_RELU_H__


#include <ostream>
#include <string>

#include "../Modules.h"
#include "../../Tensor.h"
#include "../../Functions/NonLinear/ReLU.h"

namespace cml {
namespace nn {

    template<typename T = float>
    class ReLU: public Module<T> {
        /*
        Applies the rectified linear unit function element-wise:

        ReLU(x) = max(0, x)

        Params:
            inplace - can optionally do the operation in-place. Default: False
        */

        bool inplace;

        public:
            ReLU(const bool& inplace = false): inplace {inplace} {}

            tensor<T> forward(tensor<T> x) override { return Function::ReLU(x); }

            std::ostream& print(std::ostream& out, const std::string& indent) override { return out << "ReLU {}"; }
    };

}
}

#endif // __CML_NN_NONLINEAR_RELU_H__
