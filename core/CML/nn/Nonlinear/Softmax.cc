#include "../Nonlinear.h"
#include "../../Dtypes.h"
#include "../../Functions/NonLinear/Softmax.h"

using namespace std;
using namespace cml;
using namespace cml::nn;

/***********************************************************************************
********************************* Constructors *************************************
************************************************************************************/

template<typename T>
Softmax<T>::Softmax(const bool& inplace): inplace {inplace} {}


/***********************************************************************************
*********************************** Methods ****************************************
************************************************************************************/

template<typename T>
tensor<T> Softmax<T>::forward(tensor<T> x){
    return Function::Softmax::forward(x);
}

template<typename T>
std::ostream& Softmax<T>::print(std::ostream& out, const std::string& indent){
    return out << "Softmax {}";
}


/***********************************************************************************
**************************** Template Instantiations *******************************
************************************************************************************/

INSTANTIATE_CLASS_TEMPLATES(Softmax);
