
#include "../Modules.h"

using namespace std;
using namespace cml;
using namespace cml::nn;

Sequential::Sequential() {}

Tensor Sequential::forward(const Tensor& x) {
    auto y = x;
    for (auto& submodule : submodules){
        y = (*submodule)(y);
    }
    return y;
}

