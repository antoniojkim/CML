#ifndef __CML_NN_MODULES_H__
#define __CML_NN_MODULES_H__

#include <iterator>
#include <memory>
#include <vector>

#include "Parameter.h"
#include "../Tensor.h"

#define USE_VARIADIC_CONSTRUCTOR

namespace cml {
namespace nn {
    
    class Module;
    typedef std::unique_ptr<cml::nn::Module> ModuleP;
    typedef std::vector<ModuleP> Modules;
    
    class Module {
        protected:
            std::vector<cml::nn::Parameter> params;
            Modules submodules;
        
        public:
            Module();
            // Module(Modules submodules);
            template<typename ...T>
            Module(T&&...submodules) {
                ModuleP mps[] = {std::move(submodules)...};
                this->submodules = Modules{std::make_move_iterator(std::begin(mps)),
                                     std::make_move_iterator(std::end(mps))};
            }
        
            virtual cml::Tensor forward(const cml::Tensor&) = 0;
            cml::Tensor operator()(const cml::Tensor& x){ return forward(x); }
        
            void addModule(ModuleP&);
    };
    
    template <typename T, typename...Args>
    inline std::unique_ptr<Module> new_module(Args&&...args) {
        return std::unique_ptr<Module>{new T(std::forward<Args>()...)};
    }
    
    class Sequential: public Module {
        public:
            Sequential();
            template<typename ...T>
            Sequential(T&&...submodules): Module(std::forward<T>(submodules)...) {}

            cml::Tensor forward(const cml::Tensor&) override;
    };
    
}
}

#endif // __CML_NN_MODULES_H__
