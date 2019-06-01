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

    /*
        The Module class is the base class for all neural network modules

        Modules can contain other modules, allowing them to nest in a tree like structure.
        All submodules must have the same template type

        TODO:  Add automatic casting when a module of a different template type is added.
    */
    template <typename T> 
    class Module {
        protected:
            Module<T>* parent = nullptr;
            Parameters<T> params;
            Modules<T> submodules;
            // stores mapping from string aliases to the submodules
            std::map<std::string, Module<T>*> values;
            // stores mapping from submodules to their respective aliases
            std::map<Module<T>*, std::string> keys;
            void init();

            /*
                The following method can be used to add parameters to the module.

                Note that this method is protected. While this does not prevent
                a subclass being created that contains the functionality to make
                adding parameters public, it is recommended that parameters only
                be added during module construction.
            */
            template<typename...Args>
            void addParameter(const std::string& alias, Args&&...args){
                params.add(new_parameter<T>(std::forward<Args>(args)...), alias);
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
            virtual cml::Tensor<T> forward(cml::Tensor<T>&) = 0;
            cml::Tensor<T> operator()(cml::Tensor<T>& x);
        
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
            Parameter<T>& getParam(const int& index);
            /*
                The following method can be used to get the individual parameters
                using the alias that was provided when it was added.

                The aliases will generally be specified in the documentation for
                that specific module.
                
                Since the order in which the paramters is not usually known, this
                is the recommended way to access individual parameters.
            */
            Parameter<T>& getParam(const std::string& alias);
            /*
                The following overload of the operator() is used as a shorthand for
                the method getParam(string).

                Note, this is not to be confused with the other overload for it
                which was used as a shorthand for forward. 
            */
            Parameter<T>& operator()(const std::string& alias);

            /*
                This method can be used to apply a function to each submodule.

                If recursive is set to true, it will recursively apply the function
                to each submodule's submodules and so on.
            */
            void apply(void (*fn)(Module<T>&), const bool& recursive = true);

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

    
}
}

#endif // __CML_NN_MODULES_H__
