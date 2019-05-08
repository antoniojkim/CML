
#include "../Containers.h"

using namespace std;
using namespace cml;
using namespace cml::nn;

cml::nn::ModuleList::ModuleList() {}

Tensor cml::nn::ModuleList::forward(const Tensor& x) {
    auto y = x;
    for (auto& submodule : submodules){
        y = (*submodule)(y);
    }
    return y;
}

std::ostream& cml::nn::ModuleList::print(std::ostream& out, const std::string& indent){
    out << indent << "ModuleList {" << endl;
    for (auto& submodule: submodules){
        out << indent << "    ";
        submodule->print(out, indent+"    ") << endl;
    }
    out << indent << "}";
    return out;
}

