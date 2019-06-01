#include "../Nonlinear.h"
#include "../../Dtypes.h"

using namespace std;
using namespace cml;
using namespace cml::nn;

/***********************************************************************************
********************************* Constructors *************************************
************************************************************************************/

template<typename T>
ReLU<T>::ReLU(const bool& inplace): inplace {inplace} {}


/***********************************************************************************
*********************************** Methods ****************************************
************************************************************************************/

template<typename T>
Tensor<T> ReLU<T>::forward(Tensor<T>& x){
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

template<typename T>
std::ostream& ReLU<T>::print(std::ostream& out, const std::string& indent){
    return out << "ReLU {}";
}


/***********************************************************************************
**************************** Template Instantiations *******************************
************************************************************************************/

INSTANTIATE_CLASS_TEMPLATES(ReLU);
