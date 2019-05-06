
#include <utility>

#include "../Modules.h"

using namespace std;
using namespace cml;
using namespace cml::nn;


Module::Module(){}
// Module::Module(const Modules& submodules): submodules{std::move(submodules)} {}
// Module::Module(Modules submodules): submodules{std::move(submodules)} {}
// #ifdef USE_VARIADIC_CONSTRUCTOR
// template<typename ...T>
// Module::Module(T...submodules): submodules{submodules...} {}
// #else
// Module::Module(initializer_list<ModuleP> submodules): submodules(submodules) {}
// #endif

void Module::addModule(ModuleP& m){
    submodules.emplace_back(std::move(m));
}

