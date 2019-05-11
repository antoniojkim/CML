
#include "../Linear.h"

using namespace std;
using namespace cml::nn;

Linear::Linear(const int& in_features, const int& out_features, const bool& bias): 
in_features{in_features}, out_features{out_features}, bias{bias} {
    addParameter<float>(in_features, out_features);
    addParameter<float>(out_features);
}

Parameter Linear::getWeights(){ params[0].get(); }
Parameter Linear::getBias(){ bias ? params[1].get() : nullptr; }

std::ostream& Linear::print(std::ostream& out, const std::string& indent){
    return out << "Linear:  in_features: " << in_features << 
                        "  out_features: " << out_features << "  bias: " << bias;
}
