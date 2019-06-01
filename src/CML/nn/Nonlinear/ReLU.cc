#include "../Nonlinear.h"
#include "../../Dtypes.h"
#include "../../Functions/NonLinear.h"

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
    return Function::ReLU::forward(x);
}

template<typename T>
std::ostream& ReLU<T>::print(std::ostream& out, const std::string& indent){
    return out << "ReLU {}";
}


/***********************************************************************************
**************************** Template Instantiations *******************************
************************************************************************************/

INSTANTIATE_CLASS_TEMPLATES(ReLU);
