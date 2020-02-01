#ifndef __CML_NN_NONLINEAR_TANH_H__
#define __CML_NN_NONLINEAR_TANH_H__

#include "../Modules.h"
#include "../../Tensor.h"
#include "../../Functions/NonLinear/Tanh.h"


namespace cml {
namespace nn {

    template<typename T = float>
    class Tanh: public Module<T> {
        /*
        Applies the Tanh function element-wise.

        Params:
            inplace - can optionally do the operation in-place. Default: False
        */

        bool inplace;

        public:
            // TODO: Add support for in-place
            Tanh(const bool& inplace = false): inplace {inplace} {}

            tensor<T> forward(tensor<T> x) override { return Function::Tanh::forward(x); }

            std::ostream& print(std::ostream& out, const std::string& indent) override { return out << "Tanh {}"; }
    };

}
}

#endif // __CML_NN_NONLINEAR_TANH_H__