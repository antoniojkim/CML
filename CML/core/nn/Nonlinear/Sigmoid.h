#ifndef __CML_NN_NONLINEAR_SIGMOID_H__
#define __CML_NN_NONLINEAR_SIGMOID_H__

#include "../Modules.h"
#include "../../Tensor.h"
#include "../../Functions/NonLinear/Sigmoid.h"

namespace cml {
namespace nn {

    template<typename T = float>
    class Sigmoid: public Module<T> {
        /*
        Applies the Sigmoid function element-wise.

        Params:
            inplace - can optionally do the operation in-place. Default: False
        */

        bool inplace;

        public:
            Sigmoid(const bool& inplace = false): inplace {inplace} {}

            tensor<T> forward(tensor<T> x) override { return Function::Sigmoid::forward(x); }

            std::ostream& print(std::ostream& out, const std::string& indent) override { return out << "Sigmoid {}"; }
    };

}
}

#endif // __CML_NN_NONLINEAR_SIGMOID_H__