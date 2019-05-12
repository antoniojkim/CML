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
    
    class Module;
    typedef std::unique_ptr<cml::nn::Module> ModuleP;
    typedef std::vector<ModuleP> Modules;

    template <typename T, typename...Args>
    inline std::unique_ptr<Module> new_module(Args&&...args) {
        return std::unique_ptr<Module>(new T(std::forward<Args>(args)...));
    }
    template <typename T, typename...Args>
    inline std::pair<std::string, std::unique_ptr<Module>> new_module(const std::string& key, Args&&...args) {
        return std::pair<std::string, std::unique_ptr<ModuleP>>(key, std::unique_ptr<Module>(new T(std::forward<Args>(args)...)));
    }
    
    class Module {
        protected:
            Module* parent;
            Parameters params;
            Modules submodules;
            std::map<std::string, ModuleP*> values;
            std::map<ModuleP*, std::string> keys;
            void init();
        
        public:
            Module();
            template<typename ...T>
            Module(T&&...submodules) {
                ModuleP mps[] = {std::move(submodules)...};
                this->submodules = Modules{std::make_move_iterator(std::begin(mps)),
                                           std::make_move_iterator(std::end(mps))};
                init();
            }
            Module(std::initializer_list<std::pair<std::string, ModuleP&&>>);
        
            virtual cml::Tensor forward(const cml::Tensor&) = 0;
            cml::Tensor operator()(const cml::Tensor& x){ return forward(x); }
        
            void addModule(const std::string& key, ModuleP&);
            void addModule(const std::string& key, ModuleP&&);
            void addModule(ModuleP&, const std::string& key = "");
            void addModule(ModuleP&&, const std::string& key = "");
            template<typename T, typename...Args>
            void addModule(Args&&...args){
                addModule(new_module<T>(std::forward<T>(args)...));
            }

            void addParameter(uParameter&&, const std::string& key = "");
            template<typename T>
            void addParameter(const std::string& key, const int& R, const int& C = 1){
                addParameter(new_parameter<T>(R, C), key);
            }
            
            Parameter getParam(const int& index);
            Parameter getParam(const std::string& key);
            Parameter operator()(const std::string& key){ return params[key]; }
            Parameters& getParams();
            

            void apply(void (*fn)(ModuleP&));

            Modules& getModules();
            Module& operator[](const int& index);
            Module& operator[](const std::string& key);

            virtual std::ostream& print(std::ostream&, const std::string& indent) = 0;
    };
    
}
}
std::ostream& operator<<(std::ostream&, cml::nn::Module&);

#endif // __CML_NN_MODULES_H__
