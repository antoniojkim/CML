
#include "../Containers.h"

using namespace std;
using namespace cml;
using namespace cml::nn;

cml::nn::Sequential::Sequential() {}
cml::nn::Sequential::Sequential(initializer_list<pair<string, ModuleP&&>> dict): Module{dict} {}


Tensor cml::nn::Sequential::forward(const Tensor& x) {
    auto y = x;
    for (auto& submodule : submodules){
        y = (*submodule)(y);
    }
    return y;
}

ostream& cml::nn::Sequential::print(ostream& out, const string& indent){
    out << "Sequential {" << endl;
    for (auto& submodule: submodules){
        out << indent << "    ";
        if (keys.count(&submodule) > 0){
            out << keys[&submodule] << ":  ";
        }
        submodule->print(out, indent+"    ") << endl;
    }
    out << indent << "}";
    return out;
}

