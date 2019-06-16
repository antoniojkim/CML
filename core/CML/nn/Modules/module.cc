
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
        mKeys[std::to_string(i)] = this->submodules[i].get();
        mValues[this->submodules[i].get()] = std::to_string(i);
    }
}

template<typename T>
cml::tensor<T> Module<T>::operator()(cml::tensor<T> x){
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


template<typename T>
long int Module<T>::getNumParameters(const bool& recursive){
    long int num = params.size();
    if (recursive){
        for (auto& submodule : submodules){
            num += submodule->getNumParameters();
        }
    }
    return num;
}
template<typename T>
std::vector<Parameter<T>> Module<T>::parameters(const bool& recursive){
    std::vector<Parameter<T>> parameters;
    parameters.reserve(getNumParameters(recursive));
    getParameters(parameters, recursive);
    return parameters;
}
template<typename T>
void Module<T>::getParameters(std::vector<Parameter<T>>& parameters, const bool& recursive){
    for (auto& param : params){
        parameters.emplace_back(param);
    }
    if (recursive){
        for (auto& submodule : submodules){
            submodule->getParameters(parameters, recursive);
        }
    }
}


template<typename T>
void Module<T>::grad(const bool& recursive){
    for (auto& param : params){
        param->computeGrad = true;
    }
    if (recursive){
        for (auto& submodule : submodules){
            submodule->grad(recursive);
        }
    }
}
template<typename T>
void Module<T>::noGrad(const bool& recursive){
    for (auto& param : params){
        param->computeGrad = false;
    }
    if (recursive){
        for (auto& submodule : submodules){
            submodule->grad(recursive);
        }
    }
}

template<typename T>
void Module<T>::initWeights(Randomizer::Function<T> randomizer){
    initWeights(true, randomizer);
}

template<typename T>
void Module<T>::initWeights(const bool& recursive, Randomizer::Function<T> randomizer){
    for (auto& param : params){
        param->randomize(randomizer);
    }
    if (recursive){
        for (auto& submodule : submodules){
            submodule->initWeights(recursive, randomizer);
        }
    }
}


/***********************************************************************************
****************************** Submodule Methods ***********************************
************************************************************************************/

template<typename T> Module<T>& Module<T>::addModule(Module<T>* m){
    return addModule(std::unique_ptr<Module<T>>(m));
}
template<typename T> Module<T>& Module<T>::addModule(const std::string& alias, Module<T>* m){
    return addModule(std::unique_ptr<Module<T>>(m), alias);
}
template<typename T> Module<T>& Module<T>::addModule(const string& alias, uModule<T>& m){
    return this->addModule(std::move(m), alias);
}
template<typename T> Module<T>& Module<T>::addModule(const string& alias, uModule<T>&& m){
    return this->addModule(std::move(m), alias);
}
template<typename T> Module<T>& Module<T>::addModule(uModule<T>& m, const string& alias){
    return this->addModule(std::move(m), alias);
}
template<typename T> 
Module<T>& Module<T>::addModule(uModule<T>&& m, const string& alias){
    submodules.emplace_back(std::move(m));
    submodules.back()->parent = this;
    if (alias == ""){
        auto newkey = to_string(submodules.size()-1);
        if (mKeys.count(newkey) > 0){
            ostringstream error;
            error << "alias Already Exists: " << newkey;
            throw error.str();
        }
        mKeys[newkey] = submodules.back().get();
        mValues[submodules.back().get()] = newkey;
    }
    else{
        if (mKeys.count(alias) > 0){
            ostringstream error;
            error << "alias Already Exists: " << alias;
            throw error.str();
        }
        mKeys[alias] = submodules.back().get();
        mValues[submodules.back().get()] = alias;
    }
    return *this;
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
Module<T>& Module<T>::operator[](const string& alias){
    if (mKeys.count(alias) > 0){
        return *mKeys[alias];
    }

    ostringstream error;
    error << "Invalid alias: " << alias;
    throw error.str();
}



/***********************************************************************************
****************************** Parameter Methods ***********************************
************************************************************************************/


template<typename T>
Parameter<T> Module<T>::getParam(const int& index){
    if (index >= 0 && index < (int) params.size()){
        return params[index];
    }
    else if (index < 0 && -index <= (int) params.size()){
        return params[params.size()+index];
    }

    std::ostringstream error;
    error << "Invalid index: " << index << ",  params.size() == " << params.size();
    throw error.str();
}
template<typename T>
Parameter<T> Module<T>::getParam(const string& alias){ 
    if (pKeys.count(alias) > 0){  return *(pKeys[alias]);  }
    
    std::ostringstream error;
    error << "Invalid key: " << alias;
    throw error.str();
}
template<typename T>
Parameter<T> Module<T>::operator()(const string& alias){ return getParam(alias); }
template<typename T>
Parameters<T>& Module<T>::getParams(){ return params; }


/***********************************************************************************
**************************** Template Instantiations *******************************
************************************************************************************/

INSTANTIATE_CLASS_TEMPLATES(Module);

