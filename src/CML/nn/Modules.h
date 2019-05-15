#ifndef __CML_NN_MODULES_H__
#define __CML_NN_MODULES_H__

#include <initializer_list>
#include <iostream>
#include <iterator>
#include <map>
#include <memory>
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

    template <template<typename> class T, typename U = float, typename...Args>
    inline std::unique_ptr<Module<U>> new_module(Args&&...args) {
        return std::unique_ptr<Module<U>>(new T<U>(std::forward<Args>(args)...));
    }
    template <template<typename> class T, typename U = float, typename...Args>
    inline std::pair<std::string, std::unique_ptr<Module<U>>> new_module(const std::string& key, Args&&...args) {
        return std::pair<std::string, std::unique_ptr<Module<U>>>(key, std::unique_ptr<Module<U>>(new T<U>(std::forward<Args>(args)...)));
    }
    
    template <typename T> 
    class Module {
        protected:
            Module<T>* parent = nullptr;
            Parameters<T> params;
            Modules<T> submodules;
            std::map<std::string, Module<T>*> values;
            std::map<Module<T>*, std::string> keys;
            void init();
        
        public:
            Module();
            template<typename ...U> 
            Module(U&&...submodules){
                uModule<T> mps[] = {std::move(submodules)...};
                this->submodules = Modules<T>{std::make_move_iterator(std::begin(mps)),
                                            std::make_move_iterator(std::end(mps))};
                init(); 
            }
            Module(std::initializer_list<std::pair<std::string, uModule<T>&&>> dict);
        
            virtual cml::Tensor<T> forward(const cml::Tensor<T>&) = 0;
            cml::Tensor<T> operator()(const cml::Tensor<T>& x);
        
            void addModule(const std::string& key, uModule<T>& m);
            void addModule(const std::string& key, uModule<T>&& m);
            void addModule(uModule<T>& m, const std::string& key = "");
            void addModule(uModule<T>&& m, const std::string& key = "");
            template<template<typename> typename S, typename...Args>
            void addModule(Args&&...args){
                addModule(new_module<S, T>(std::forward<Args>(args)...));
            }


            void addParameter(uParameter<T>&& p, const std::string& key = "");
            template<typename...Args>
            void addParameter(const std::string& key, Args&&...args){
                addParameter(new_parameter<T>(std::forward<Args>(args)...), key);
            }


            void apply(void (*fn)(Module<T>&), const bool& recursive = true);

            Modules<T>& getModules();
            Module<T>& operator[](const int& index);
            Module<T>& operator[](const std::string& key);

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
