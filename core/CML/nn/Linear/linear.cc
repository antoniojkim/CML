
#include "../../Dtypes.h"
#include "../Linear.h"
#include "../../Functions/Linear.h"

using namespace std;
using namespace cml::nn;

/***********************************************************************************
********************************* Constructors *************************************
************************************************************************************/

template<typename T>
Linear<T>::Linear(const int& in_features, const int& out_features, const bool& bias): 
in_features{in_features}, out_features{out_features}, bias{bias} {
    addParameter("weights", in_features, out_features);
    if (bias) addParameter("bias", out_features);
}


/***********************************************************************************
*********************************** Methods ****************************************
************************************************************************************/

template<typename T>
Parameter<T>& Linear<T>::getWeights(){ return params[0]; }
template<typename T>
Parameter<T>& Linear<T>::getBias(){
    if (bias) return params[1];
    throw "Attempting to get bias from Linear layer without bias";
}


template<typename T>
cml::tensor<T> Linear<T>::forward(cml::tensor<T> x){
    return bias ? Function::Linear::forward(x, getWeights(), getBias(), gradientMode) :
                  Function::Linear::forward(x, getWeights(), gradientMode);
}

template<typename T>
std::ostream& Linear<T>::print(std::ostream& out, const std::string& indent){
    return out << "Linear { in_features: " << in_features << 
                        "  out_features: " << out_features << "  bias: " << (bias ? "true" : "false") << " }";
}


/***********************************************************************************
**************************** Template Instantiations *******************************
************************************************************************************/

INSTANTIATE_CLASS_TEMPLATES(Linear);
