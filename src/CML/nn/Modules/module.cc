
#include <cstdlib>
#include <utility>

#include "../Modules.h"

using namespace std;
using namespace cml;
using namespace cml::nn;


void Module::init(){
    for (unsigned int i = 0; i<this->submodules.size(); ++i){
        values[std::to_string(i)] = &(this->submodules[i]);
        keys[&(this->submodules[i])] = std::to_string(i);
    }
}

Module::Module(){ init(); }
Module::Module(std::initializer_list<std::pair<std::string, ModuleP&&>> dict){
    submodules.reserve(dict.size());
    for (auto& kv : dict){
        addModule(std::forward<ModuleP>(kv.second), kv.first);
    }
}

void Module::addModule(ModuleP& m, const std::string& key){ this->addModule(std::move(m), key); }
void Module::addModule(const std::string& key, ModuleP& m){ this->addModule(std::move(m), key); }
void Module::addModule(const std::string& key, ModuleP&& m){ this->addModule(std::move(m), key); }
void Module::addModule(ModuleP&& m, const std::string& key){
    submodules.emplace_back(std::move(m));
    submodules.back()->parent = this;
    if (key == ""){
        auto newkey = to_string(submodules.size());
        if (values.count(newkey) > 0){
            ostringstream error;
            error << "Key Already Exists: " << newkey;
            throw error.str();
        }
        values[newkey] = &(submodules.back());
        keys[&(submodules.back())] = newkey;
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

void Module::addParameter(uParameter&& p, const std::string& key){
    params.add(std::move(p), key);
}
Parameter Module::getParam(const int& index){ return params[index]; }
Parameter Module::getParam(const std::string& key){ return params[key]; }
Parameters& Module::getParams(){ return params; }

void Module::apply(void (*fn)(ModuleP&)){
    for (auto& submodule : submodules){
        fn(submodule);
    }
}

Modules& Module::getModules(){ return submodules; }
Module& Module::operator[](const int& index){
    if (index >= 0 && index < (int) submodules.size()){
        return *submodules[index];
    }
    else if (index < 0 && -index <= (int) submodules.size()){
        return *submodules[submodules.size()+index];
    }
    
    ostringstream error;
    error << "Invalid index: " << index << ",  submodules.size() == " << submodules.size() << endl;
    throw error.str();
}
Module& Module::operator[](const string& key){
    if (values.count(key) > 0){
        return *(*values[key]);
    }
    
    ostringstream error;
    error << "Invalid key: " << key;
    throw error.str();
}


std::ostream& operator<<(std::ostream& out, Module& module){
    return module.print(out, "");
}

