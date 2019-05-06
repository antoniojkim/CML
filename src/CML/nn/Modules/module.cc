
#include <utility>

#include "../Modules.h"

using namespace std;
using namespace cml;
using namespace cml::nn;


Module::Module(){}

void Module::addModule(ModuleP& m){
    submodules.emplace_back(std::move(m));
}

