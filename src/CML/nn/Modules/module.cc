
#include <cstdlib>
#include <utility>

#include "../Modules.h"
#include "../../Dtypes.h"

using namespace std;
using namespace cml;
using namespace cml::nn;

/***********************************************************************************
********************************* Constructors *************************************
************************************************************************************/

template<typename T>
Module<T>::Module(){ init(); }
template<typename T>
Module<T>::Module(std::initializer_list<Module<T>*> submodules){
    this->submodules.reserve(submodules.size());
    for(auto submodule: submodules){
        addModule(std::unique_ptr<Module<T>>(submodule));
    }
    init();
}
template<typename T>
Module<T>::Module(std::initializer_list<std::pair<std::string, Module<T>*>> dict){
    submodules.reserve(dict.size());
    for (auto& kv : dict){
        addModule(std::unique_ptr<Module<T>>(kv.second), kv.first);
    }
}


/***********************************************************************************
*********************************** Methods ****************************************
************************************************************************************/

template<typename T>
void Module<T>::init(){
    for (unsigned int i = 0; i<this->submodules.size(); ++i){
        values[std::to_string(i)] = this->submodules[i].get();
        keys[this->submodules[i].get()] = std::to_string(i);
    }
}

template<typename T>
cml::Tensor<T> Module<T>::operator()(const cml::Tensor<T>& x){
    return forward(x);
}

template<typename T>
void Module<T>::apply(void (*fn)(Module<T>&), const bool& recursive){
    fn(*this);
    if (recursive){
        for (auto& submodule : submodules){
            submodule->apply(fn);
        }
    }
}


/***********************************************************************************
****************************** Submodule Methods ***********************************
************************************************************************************/

template<typename T> void Module<T>::addModule(const string& key, uModule<T>& m){ this->addModule(std::move(m), key); }
template<typename T> void Module<T>::addModule(const string& key, uModule<T>&& m){ this->addModule(std::move(m), key); }
template<typename T> void Module<T>::addModule(uModule<T>& m, const string& key){ this->addModule(std::move(m), key); }
template<typename T> 
void Module<T>::addModule(uModule<T>&& m, const string& key){
    submodules.emplace_back(std::move(m));
    submodules.back()->parent = this;
    if (key == ""){
        auto newkey = to_string(submodules.size());
        if (values.count(newkey) > 0){
            ostringstream error;
            error << "Key Already Exists: " << newkey;
            throw error.str();
        }
        values[newkey] = submodules.back().get();
        keys[submodules.back().get()] = newkey;
    }
    else{
        if (values.count(key) > 0){
            ostringstream error;
            error << "Key Already Exists: " << key;
            throw error.str();
        }
        values[key] = submodules.back().get();
        keys[submodules.back().get()] = key;
    }
}


template<typename T>
Modules<T>& Module<T>::getModules(){ return submodules; }
template<typename T>
Module<T>& Module<T>::operator[](const int& index){
    if (index >= 0 && index < (int) submodules.size()){
        return *submodules[index];
    }
    else if (index < 0 && -index <= (int) submodules.size()){
        return *submodules[submodules.size()+index];
    }
    
    ostringstream error;
    error << "Invalid index: " << index << ",  submodules.size() == " << submodules.size();
    throw error.str();
}
template<typename T>
Module<T>& Module<T>::operator[](const string& key){
    if (values.count(key) > 0){
        return *values[key];
    }
    
    ostringstream error;
    error << "Invalid key: " << key;
    throw error.str();
}



/***********************************************************************************
****************************** Parameter Methods ***********************************
************************************************************************************/

template<typename T> 
void Module<T>::addParameter(uParameter<T>&& p, const string& key){
    params.add(std::move(p), key);
}


template<typename T>
Parameter<T>& Module<T>::getParam(const int& index){ return params[index]; }
template<typename T>
Parameter<T>& Module<T>::getParam(const string& key){ return params[key]; }
template<typename T>
Parameter<T>& Module<T>::operator()(const string& key){ return params[key]; }
template<typename T>
Parameters<T>& Module<T>::getParams(){ return params; }


/***********************************************************************************
**************************** Template Instantiations *******************************
************************************************************************************/

INSTANTIATE_CLASS_TEMPLATES(Module);


