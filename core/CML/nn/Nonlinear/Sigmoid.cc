#include "../Nonlinear.h"
#include "../../Dtypes.h"
#include "../../Functions/NonLinear/Sigmoid.h"

using namespace std;
using namespace cml;
using namespace cml::nn;

/***********************************************************************************
********************************* Constructors *************************************
************************************************************************************/

template<typename T>
Sigmoid<T>::Sigmoid(const bool& inplace): inplace {inplace} {}


/***********************************************************************************
*********************************** Methods ****************************************
************************************************************************************/

template<typename T>
tensor<T> Sigmoid<T>::forward(tensor<T> x){
    return Function::Sigmoid::forward(x);
}

template<typename T>
std::ostream& Sigmoid<T>::print(std::ostream& out, const std::string& indent){
    return out << "Sigmoid {}";
}


/***********************************************************************************
**************************** Template Instantiations *******************************
************************************************************************************/

INSTANTIATE_CLASS_TEMPLATES(Sigmoid);
