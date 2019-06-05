#ifndef __CML_FUNCTIONS_LOSS_MEANSQUARED_H__
#define __CML_FUNCTIONS_LOSS_MEANSQUARED_H__

#include "../../Tensor.h"
#include "../../DCG.h"

namespace cml {
namespace Function {
    
    struct MSELoss {
        
        template<typename T>
        static tensor<T> backward(tensor<T> output){
            throw "Unimplemented ReLU::backward(tensor<T>& output)";
        }
        
        template<typename T>
        static tensor<T> forward(tensor<T>& input){
            auto t = make_tensor<T>(static_cast<DMatrix<T>>(
                input->data().cwiseAbs()
            ));
            t->graph = make_graph<T>(input->graph);
            t->graph->f = ReLU::backward<T>;
            return t;
        }

    };

    template<typename T>
    inline tensor<T> ReLU(tensor<T>& input){ return ReLU::forward(input); }

};
};

#endif // __CML_FUNCTIONS_LOSS_MEANSQUARED_H__
