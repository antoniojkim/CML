
#include "../Containers.h"

using namespace std;
using namespace cml;
using namespace cml::nn;

cml::nn::Sequential::Sequential() {}
#ifndef USE_VARIADIC_CONSTRUCTOR
cml::nn::Sequential::Sequential(std::initializer_list<ModuleP&&> submodules): Module{submodules} {}
#endif

Tensor cml::nn::Sequential::forward(const Tensor& x) {
    auto y = x;
    for (auto& submodule : submodules){
        y = (*submodule)(y);
    }
    return y;
}

std::ostream& cml::nn::Sequential::print(std::ostream& out, const std::string& indent){
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

