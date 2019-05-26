#ifndef __CML_NN_MODULES_H__
#define __CML_NN_MODULES_H__

#include <functional>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <memory>
#include <utility>
#include <vector>

// #include "Linear.h"
// #include "Nonlinear.h"
#include "Parameter.h"
#include "../Tensor.h"

namespace cml {
namespace nn {
    
    template<typename T> class Module;
    template<typename T>
    using uModule = std::unique_ptr<cml::nn::Module<T>>;
    template<typename T>
    using Modules = std::vector<uModule<T>>;
    
    template <typename T> 
    class Module {
        protected:
            Module<T>* parent = nullptr;
            Parameters<T> params;
            Modules<T> submodules;
            std::map<std::string, Module<T>*> values;
            std::map<Module<T>*, std::string> keys;
            std::list<std::string> keyBuffer;
            void init();
            void init(std::initializer_list<Module<T>*>);
            void init(std::initializer_list<std::pair<std::string, Module<T>*>>);

            void addParameter(uParameter<T>&& p, const std::string& key = "");
            template<typename...Args>
            void addParameter(const std::string& key, Args&&...args){
                addParameter(new_parameter<T>(std::forward<Args>(args)...), key);
            }
        
        public:
            Module();
            Module(std::initializer_list<Module<T>*>);
            Module(std::initializer_list<std::pair<std::string, Module<T>*>>);
        
            virtual cml::Tensor<T> forward(const cml::Tensor<T>&) = 0;
            cml::Tensor<T> operator()(const cml::Tensor<T>& x);
        
            Module<T>& addModule(Module<T>* m);
            Module<T>& addModule(const std::string& key, Module<T>* m);
            Module<T>& addModule(const std::string& key, uModule<T>& m);
            Module<T>& addModule(const std::string& key, uModule<T>&& m);
            Module<T>& addModule(uModule<T>& m, const std::string& key = "");
            Module<T>& addModule(uModule<T>&& m, const std::string& key = "");
            template<typename S, typename...Args>
            Module<T>& addModule(Args&&...args){
                return addModule(std::unique_ptr<Module<T>>(new S(std::forward<Args>(args)...)));
            }
            template<typename S, typename...Args>
            Module<T>& addModule(const std::string& key, Args&&...args){
                return addModule(std::unique_ptr<Module<T>>(new S(std::forward<Args>(args)...)), key);
            }
            template<template<typename> typename S, typename...Args>
            Module<T>& addModule(Args&&...args){
                return addModule(std::unique_ptr<Module<T>>(new S<T>(std::forward<Args>(args)...)));
            }
            template<template<typename> typename S, typename...Args>
            Module<T>& addModule(const std::string& key, Args&&...args){
                return addModule(std::unique_ptr<Module<T>>(new S<T>(std::forward<Args>(args)...)), key);
            }


            void apply(void (*fn)(Module<T>&), const bool& recursive = true);

            Modules<T>& getModules();
            Module<T>& operator[](const int& index);
            Module<T>& operator[](const std::string& key);
            Module<T>& operator()(const std::string& key, Module<T>*);

            Parameter<T>& getParam(const int& index);
            Parameter<T>& getParam(const std::string& key);
            Parameter<T>& operator()(const std::string& key);
            Parameters<T>& getParams();

            virtual std::ostream& print(std::ostream&, const std::string& indent) = 0;

    };
    
    template<typename T>
    std::ostream& operator<<(std::ostream& out, cml::nn::Module<T>& module){
        return module.print(out, "");
    }

    
}
}

#endif // __CML_NN_MODULES_H__
