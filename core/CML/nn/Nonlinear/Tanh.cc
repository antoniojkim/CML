#include "../Nonlinear.h"
#include "../../Dtypes.h"
#include "../../Functions/NonLinear/Tanh.h"

using namespace std;
using namespace cml;
using namespace cml::nn;

/***********************************************************************************
********************************* Constructors *************************************
************************************************************************************/

template<typename T>
Tanh<T>::Tanh(const bool& inplace): inplace {inplace} {}


/***********************************************************************************
*********************************** Methods ****************************************
************************************************************************************/

template<typename T>
tensor<T> Tanh<T>::forward(tensor<T> x){
    return Function::Tanh::forward(x);
}

template<typename T>
std::ostream& Tanh<T>::print(std::ostream& out, const std::string& indent){
    return out << "Tanh {}";
}


/***********************************************************************************
**************************** Template Instantiations *******************************
************************************************************************************/

INSTANTIATE_CLASS_TEMPLATES(ReLU);
