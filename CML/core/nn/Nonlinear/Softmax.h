#ifndef __CML_NN_NONLINEAR_SOFTMAX_H__
#define __CML_NN_NONLINEAR_SOFTMAX_H__


#include "../Modules.h"
#include "../../Tensor.h"
#include "../../Functions/NonLinear/Softmax.h"


namespace cml {
namespace nn {

    template<typename T = float>
    class Softmax: public Module<T> {
        /*
        Applies the Softmax function element-wise.

        Params:
            inplace - can optionally do the operation in-place. Default: False
        */

        bool inplace;

        public:
            Softmax(const bool& inplace = false): inplace {inplace} {}

            tensor<T> forward(tensor<T> x) override { return Function::Softmax::forward(x); }

            std::ostream& print(std::ostream& out, const std::string& indent) override { return out << "Softmax {}"; }
    };

}
}

#endif // __CML_NN_NONLINEAR_SOFTMAX_H__