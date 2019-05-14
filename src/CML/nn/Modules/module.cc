
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

template<typename T> template<typename ...U>
Module<T>::Module(U&&...submodules) {
    uModule<T> mps[] = {std::move(submodules)...};
    this->submodules = Modules<T>{std::make_move_iterator(std::begin(mps)),
                                  std::make_move_iterator(std::end(mps))};
    init(); 
}

template<typename T>
Module<T>::Module(std::initializer_list<std::pair<string, uModule<T>&&>> dict){
    submodules.reserve(dict.size());
    for (auto& kv : dict){
        addModule(std::forward<uModule<T>>(kv.second), kv.first);
    }
}


/***********************************************************************************
*********************************** Methods ****************************************
************************************************************************************/

template<typename T>
void Module<T>::init(){
    for (unsigned int i = 0; i<this->submodules.size(); ++i){
        values[std::to_string(i)] = &(this->submodules[i]);
        keys[&(this->submodules[i])] = std::to_string(i);
    }
}

template<typename T>
cml::Tensor<T> Module<T>::operator()(const cml::Tensor<T>& x){
    return forward(x);
}

template<typename T>
void Module<T>::apply(void (*fn)(uModule<T>&), const bool& recursive){
    fn(*this);
    if (recursive){
        for (auto& submodule : submodules){
            submodule->apply(fn);
        }
    }
}

// template<typename U>
// uModule<T>& to(){
//     // Parameters tmp;
//     for (auto& kv : params.values){
//         // kv.second = kv.second->to<T>();
//         auto& t = kv.second->toTensor();
//     }
//     for (auto& submodule : submodules){
//         submodule->to<U>();
//     }
//     return *this;
// }


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
template<typename T> template<template<typename> typename S, typename...Args>
void Module<T>::addModule(Args&&...args){
    addModule(new_module<S, T>(std::forward<Args>(args)...));
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
template<typename T> template<typename...Args>
void Module<T>::addParameter(const string& key, Args&&...args){
    addParameter(new_parameter<T>(std::forward<Args>(args)...), key);
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
*********************************** Other ******************************************
************************************************************************************/

template<typename T>
std::ostream& operator<<(std::ostream& out, cml::nn::Module<T>& module){
    return module.print(out, "");
}


/***********************************************************************************
**************************** Template Instantiations *******************************
************************************************************************************/

INSTANTIATE_TEMPLATES(Module);


