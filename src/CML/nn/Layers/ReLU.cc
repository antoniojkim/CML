#include "../Layers.h"

using namespace cml;
using namespace cml::nn;

ReLU::ReLU(const bool& inplace): inplace {inplace} {}

Tensor ReLU::forward(const Tensor& x){
//     if (inplace){
//         for (auto& e : x){
//             if (e < 0) e = 0;
//         }
        return x;
//     }
    
//     Variable y {x};
//     for (auto& e : y){
//         if (e < 0) e = 0;
//     }
//     return y;
}

// Variable ReLU::backpropogation(const Variable& x){
//     return x;
// }
