
#include <utility>

#include "../Modules.h"

using namespace std;
using namespace cml;
using namespace cml::nn;


Module::Module(){}
Module::Module(std::vector<ModuleP>& submodules): submodules{std::move(submodules)} {}

void Module::addModule(ModuleP& m){
    submodules.emplace_back(std::move(m));
}

