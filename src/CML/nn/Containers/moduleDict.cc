
#include "../Containers.h"

using namespace std;
using namespace cml;
using namespace cml::nn;

cml::nn::ModuleDict::ModuleDict() {}
cml::nn::ModuleDict::ModuleDict(initializer_list<pair<string, ModuleP&&>> dict): Module{dict} {}

Tensor cml::nn::ModuleDict::forward(const Tensor& x) {
    auto y = x;
    for (auto& submodule : submodules){
        y = (*submodule)(y);
    }
    return y;
}

ostream& cml::nn::ModuleDict::print(ostream& out, const string& indent){
    out << "ModuleDict {" << endl;
    for (auto& submodule: submodules){
        out << indent << "    " << keys[&submodule] << ":  ";
        submodule->print(out, indent+"    ") << endl;
    }
    out << indent << "}";
    return out;
}

