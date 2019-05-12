
#include "../Linear.h"

using namespace std;
using namespace cml::nn;

Linear::Linear(const int& in_features, const int& out_features, const bool& bias): 
in_features{in_features}, out_features{out_features}, bias{bias} {
    addParameter<float>("weights", in_features, out_features);
    if (bias) addParameter<float>("bias", out_features);
}

Parameter Linear::getWeights(){ return params[0]; }
Parameter Linear::getBias(){
    if (bias) return params[1];
    throw "Attempting to get bias from Linear layer without bias";
}


cml::Tensor Linear::forward(const cml::Tensor& x){
    return x;
}

std::ostream& Linear::print(std::ostream& out, const std::string& indent){
    return out << "Linear { in_features: " << in_features << 
                        "  out_features: " << out_features << "  bias: " << (bias ? "true" : "false") << " }";
}
