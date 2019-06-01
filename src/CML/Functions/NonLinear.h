#ifndef __CML_FUNCTIONS_NONLINEAR_H__
#define __CML_FUNCTIONS_NONLINEAR_H__

#include "../Tensor.h"
#include "../DCG.h"

namespace cml {
namespace Function {
    
    struct ReLU {
        
        template<typename T>
        static Tensor<T> backward(Tensor<T>& output){
            throw "Unimplemented ReLU::backward(Tensor<T>& output)";
        }
        
        template<typename T>
        static Tensor<T> forward(Tensor<T>& input){
            auto t = Tensor<T>(static_cast<DMatrix<T>>(
                input.data().cwiseAbs()
            ));
            t.graph = new DCG<T>(input.graph);
            t.graph->f = ReLU::backward<T>;
            return t;
        }

    };

    template<typename T>
    inline Tensor<T> ReLU(Tensor<T>& input){ return ReLU::forward(input); }


};
};

#endif // __CML_FUNCTIONS_NONLINEAR_H__
