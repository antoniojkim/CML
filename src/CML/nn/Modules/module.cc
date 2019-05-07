
#include <cstdlib>
#include <utility>

#include "../Modules.h"

using namespace std;
using namespace cml;
using namespace cml::nn;


Module::Module(){}
#ifndef USE_VARIADIC_CONSTRUCTOR
Module::Module(std::initializer_list<ModuleP> submodules){
    this->submodules.reserve(submodules.size());
    for (auto& submodule : submodules){
        Module* tmp = submodule.get();
        submodule.release();
        addModule(ModuleP(tmp));
    }
}
#endif

void Module::addModule(ModuleP& m, const std::string& key){ this->addModule(std::move(m), key); }
void Module::addModule(const std::string& key, ModuleP& m){ this->addModule(std::move(m), key); }
void Module::addModule(const std::string& key, ModuleP&& m){ this->addModule(std::move(m), key); }
void Module::addModule(ModuleP&& m, const std::string& key){
    submodules.emplace_back(std::move(m));
    if (key == ""){
        ostringstream newkey;
        newkey << submodules.size();
        if (values.count(newkey.str()) > 0){
            ostringstream error;
            error << "Key Already Exists: " << newkey.str();
            throw error.str();
        }
        values[newkey.str()] = &(submodules.back());
        keys[&(submodules.back())] = newkey.str();
    }
    else{
        if (values.count(key) > 0){
            ostringstream error;
            error << "Key Already Exists: " << key;
            throw error.str();
        }
        values[key] = &(submodules.back());
        keys[&(submodules.back())] = key;
    }
}

void Module::apply(void (*fn)(ModuleP&)){
    for (auto& submodule : submodules){
        fn(submodule);
    }
}

Modules& Module::getModules(){ return submodules; }
ModuleP& Module::operator[](const int& index){
    if (index >= 0 && index < (int) submodules.size()){
        return submodules[index];
    }
    else if (index < 0 && -index <= (int) submodules.size()){
        return submodules[submodules.size()+index];
    }
    
    ostringstream error;
    error << "Invalid index: " << index << ",  submodules.size() == " << submodules.size() << endl;
    throw error.str();
}
ModuleP& Module::operator[](const string& key){
    if (values.count(key) > 0){
        return *values[key];
    }
    
    ostringstream error;
    error << "Invalid key: " << key;
    throw error.str();
}


std::ostream& operator<<(std::ostream& out, Module& module){
    return module.print(out, "");
}

