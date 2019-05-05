#ifndef __CML_NN_MODULES_H__
#define __CML_NN_MODULES_H__

#include <memory>
#include <vector>

#include "Parameter.h"
#include "../Tensor.h"

namespace cml {
namespace nn {
    
    class Module;
    typedef std::unique_ptr<cml::nn::Module> ModuleP;
    
    class Module {
        protected:
            std::vector<cml::nn::Parameter> params;
            std::vector<ModuleP> submodules;
        
        public:
            Module();
            Module(std::vector<ModuleP>& submodules);
        
            virtual cml::Tensor forward(const cml::Tensor&) = 0;
            cml::Tensor operator()(const cml::Tensor& x){
                return forward(x);
            }
        
            void addModule(ModuleP&);
    };
    
    template <typename T, typename...Args>
    inline std::unique_ptr<Module> new_module(Args&&...args) {
        return std::unique_ptr<Module>{new T(std::forward<Args>()...)};
    }
    
    class Sequential: public Module {
        public:
            Sequential();
            Sequential(std::vector<ModuleP>&);
            Sequential(std::vector<ModuleP>&&);

            cml::Tensor forward(const cml::Tensor&) override;
    };
    
}
}

#endif // __CML_NN_MODULES_H__
