
#include "../Modules.h"

using namespace std;
using namespace cml;
using namespace cml::nn;

Sequential::Sequential() {}
// Sequential::Sequential(const Modules& submodules): Module{std::move(submodules)} {}
// Sequential::Sequential(Modules&& submodules): Module{std::move(submodules)} {}
// #ifdef USE_VARIADIC_CONSTRUCTOR
// template<typename ...T>
// Sequential::Sequential(T...submodules): Module{submodules...} {}
// #else
// Sequential::Sequential(initializer_list<ModuleP> submodules): Module{submodules} {}
// #endif

Tensor Sequential::forward(const Tensor& x) {
    auto y = x;
    for (auto& submodule : submodules){
        y = (*submodule)(y);
    }
    return y;
}

