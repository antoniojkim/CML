#ifndef __CML_NN_MODULES_MODULES_H__
#define __CML_NN_MODULES_MODULES_H__

#include <functional>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <memory>
#include <utility>
#include <vector>

#include "../../Tensor.h"
#include "../../../Utils/Random.h"

namespace cml {
namespace nn {
    
    template<typename T> class Module;
    template<typename T>
    using uModule = std::unique_ptr<cml::nn::Module<T>>;
    template<typename T>
    using Modules = std::vector<uModule<T>>;

    /*
        The Module class is the base class for all neural network modules

        Modules can contain other modules, allowing them to nest in a tree like structure.
        All submodules must have the same template type

        TODO:  Add automatic casting when a module of a different template type is added.
    */
    template <typename T> 
    class Module {
        protected:
            Modules<T> submodules;
            Parameters<T> params;
            // stores mapping from std::string aliases to the submodules
            std::map<std::string, Module<T>*> mKeys;
            // stores mapping from submodules to the std::string aliases
            std::map<Module<T>*, std::string> mValues;
            // stores mapping from std::string aliases to the parameters
            std::map<std::string, Parameter<T>> pKeys;
            void init();
            void getParameters(std::vector<tensor<T>>&, const bool& recursive = true);

            /*
                The following method can be used to add parameters to the module.
                Note that this method is protected. While this does not prevent
                a subclass being created that contains the functionality to make
                adding parameters public, it is recommended that parameters only
                be added during module construction.
            */
            template<typename...Args>
            void addParameter(const std::string& alias, Args&&...args){
                params.emplace_back(make_tensor<T>(std::forward<Args>(args)...));
                if (alias != ""){ pKeys[alias] = params.back(); }
            }
            
        public:
            /*
                Empty Module constructor. Submodules can be added after construction using the 
                addModule methods.
            */
            Module();
            /*
                Constructs the Module with the following list of Modules.
                Although it expects raw pointers, the pointers should be to heap
                allocated Module objects.
                In addition, it will assume ownwership of whatever modules it is passed in.
                That is, it will free any and all submodules when it goes out of scope.
            */
            Module(std::initializer_list<Module<T>*>);
            /*
                Similar to above constructor with the exception that pairs of strings and
                module pointers are passed in. This assigns an alias to the module
                that can be used to reference it in the future.
            */
            Module(std::initializer_list<std::pair<std::string, Module<T>*>>);
        
            /*
                The forward method is a pure virtual method that must be overwritten by the subclass.
                It is called when forward propagating through the model.
                The operator() has been overloaded as a shorthand to call forward

                    e.g.    Instead of model.forward(x), you can use model(x)
            */
            virtual cml::tensor<T> forward(cml::tensor<T>) = 0;
            cml::tensor<T> operator()(cml::tensor<T> x);
        
            /*
                The following methods allow you to add a submodule to your module.
                Multiple overloads are declared for ease of use, but they all perform 
                the same action.

                Methods that contain an alias parameter can be used to set an alias for
                the submodule that can be used to reference it in the future.

                Note that whatever submodule you pass in, the current module will assume
                ownership of it. That is, it will free any and all submodules 
                when it goes out of scope.
            */
            Module<T>& addModule(Module<T>* m);
            Module<T>& addModule(const std::string& alias, Module<T>* m);
            Module<T>& addModule(const std::string& alias, uModule<T>& m);
            Module<T>& addModule(const std::string& alias, uModule<T>&& m);
            Module<T>& addModule(uModule<T>& m, const std::string& alias = "");
            Module<T>& addModule(uModule<T>&& m, const std::string& alias = "");
            template<typename S, typename...Args>
            Module<T>& addModule(Args&&...args){
                return addModule(std::unique_ptr<Module<T>>(new S(std::forward<Args>(args)...)));
            }
            template<template<typename> typename S, typename...Args>
            Module<T>& addModule(Args&&...args){
                return addModule(std::unique_ptr<Module<T>>(new S<T>(std::forward<Args>(args)...)));
            }


            Modules<T>& getModules();
            /*
                The following overload of the operator[] is used to get individual
                modules in the order that they were added. i.e., the first module
                added would be at index 0.

                In addition, negative indexing is supported. i.e., the last module
                added would be at index -1.

                Range checking is performed to make sure you are not indexing out of bounds.
                An exception is thrown if the index provided is out of bounds.
            */
            Module<T>& operator[](const int& index);
            /*
                The following overload of the operator[] is used to get individual
                modules using the alias that was provided when it was added.

                An exception is thrown if the alias provided does not exist.
            */
            Module<T>& operator[](const std::string& alias);


            Parameters<T>& getParams();
            /*
                The following method can be used to get the invidual parameters
                in the order that they were added. i.e., the first parameter added
                would be at index 0.

                In addition, negative indexing is supported. i.e., the last parameter
                added would be at index -1.

                Note that generally, the order of parameters is not usually known.
                So, this method should be used with caution.
            */
            Parameter<T> getParam(const int& index);
            /*
                The following method can be used to get the individual parameters
                using the alias that was provided when it was added.

                The aliases will generally be specified in the documentation for
                that specific module.
                
                Since the order in which the paramters is not usually known, this
                is the recommended way to access individual parameters.
            */
            Parameter<T> getParam(const std::string& alias);
            /*
                The following overload of the operator() is used as a shorthand for
                the method getParam(std::string).

                Note, this is not to be confused with the other overload for it
                which was used as a shorthand for forward. 
            */
            Parameter<T> operator()(const std::string& alias);

            /*
                This method will get the number of parameters in the module.
                If the recursive flag is set, it will recursively get the 
                number of paramters of all submodules.
            */
            virtual long int getNumParameters(const bool& recursive = true);
            /*
                This method will return a vector of pointers to the parameters.
                This method is different from getParams as it is getting pointers
                to the parameters and optionally getting pointers to parameteters
                of submodules as well.
            */
            virtual std::vector<tensor<T>> parameters(const bool& recursive = true);

            /*
                This method can be used to apply a function to each submodule.

                If recursive is set to true, it will recursively apply the function
                to each submodule's submodules and so on.
            */
            void apply(void (*fn)(Module<T>&), const bool& recursive = true);

            /*
                This method sets the computeGrad field for all
                parameters to true.
            */
            void grad(const bool& recursive = true);
            /*
                This method sets the computeGrad field for all
                parameters to false.
            */
            void noGrad(const bool& recursive = true);

            /*
                Initializes weight parameters
            */
            void initWeights(Random::Function<T> r = &Random::Gaussian<T>);
            void initWeights(const bool& recursive, Random::Function<T> r = &Random::Gaussian<T>);

            /*
                This pure virtual method is used to simply print out the module.
                Since modules may contain other modules, an indent is specified for
                prettier printing. The indent is empty by default.
            */
            virtual std::ostream& print(std::ostream&, const std::string& indent = "") = 0;

    };
    
    template<typename T>
    std::ostream& operator<<(std::ostream& out, cml::nn::Module<T>& module){
        return module.print(out, "");
    }



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
    void Module<T>::initWeights(Random::Function<T> r){
        initWeights(true, r);
    }

    template<typename T>
    void Module<T>::initWeights(const bool& recursive, Random::Function<T> r){
        for (auto& param : params){
            param->randomize(r);
        }
        if (recursive){
            for (auto& submodule : submodules){
                submodule->initWeights(recursive, r);
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
    template<typename T> Module<T>& Module<T>::addModule(const std::string& alias, uModule<T>& m){
        return this->addModule(std::move(m), alias);
    }
    template<typename T> Module<T>& Module<T>::addModule(const std::string& alias, uModule<T>&& m){
        return this->addModule(std::move(m), alias);
    }
    template<typename T> Module<T>& Module<T>::addModule(uModule<T>& m, const std::string& alias){
        return this->addModule(std::move(m), alias);
    }
    template<typename T> 
    Module<T>& Module<T>::addModule(uModule<T>&& m, const std::string& alias){
        submodules.emplace_back(std::move(m));
        if (alias == ""){
            auto newkey = std::to_string(submodules.size()-1);
            if (mKeys.count(newkey) > 0){
                std::ostringstream error;
                error << "alias Already Exists: " << newkey;
                throw error.str();
            }
            mKeys[newkey] = submodules.back().get();
            mValues[submodules.back().get()] = newkey;
        }
        else{
            if (mKeys.count(alias) > 0){
                std::ostringstream error;
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
        
        std::ostringstream error;
        error << "Invalid index: " << index << ",  submodules.size() == " << submodules.size();
        throw error.str();
    }
    template<typename T>
    Module<T>& Module<T>::operator[](const std::string& alias){
        if (mKeys.count(alias) > 0){
            return *mKeys[alias];
        }

        std::ostringstream error;
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
    Parameter<T> Module<T>::getParam(const std::string& alias){ 
        if (pKeys.count(alias) > 0){  return pKeys[alias];  }
        
        std::ostringstream error;
        error << "Invalid key: " << alias;
        throw error.str();
    }
    template<typename T>
    Parameter<T> Module<T>::operator()(const std::string& alias){ return getParam(alias); }
    template<typename T>
    Parameters<T>& Module<T>::getParams(){ return params; }

    
}
}

#endif // __CML_NN_MODULES_MODULES_H__
