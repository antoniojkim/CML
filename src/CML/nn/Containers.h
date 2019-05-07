#ifndef __CML_NN_CONTAINERS_H__
#define __CML_NN_CONTAINERS_H__

#include "Modules.h"

#include <utility>

namespace cml {
namespace nn {
    
    class Sequential: public Module {
        public:
            Sequential();
#ifdef USE_VARIADIC_CONSTRUCTOR
            template<typename ...T>
            Sequential(T&&...submodules): Module(std::forward<T>(submodules)...) {}
#else
            Sequential(std::initializer_list<ModuleP&&> submodules);
#endif

            cml::Tensor forward(const cml::Tensor&) override;

            std::ostream& print(std::ostream&, const std::string& indent) override;
    };
    
    class ModuleList: public Module {
        public:
            ModuleList();
#ifdef USE_VARIADIC_CONSTRUCTOR
            template<typename ...T>
            ModuleList(T&&...submodules): Module(std::forward<T>(submodules)...) {}
#else
            ModuleList(std::initializer_list<ModuleP&&> submodules);
#endif

            cml::Tensor forward(const cml::Tensor&) override;

            std::ostream& print(std::ostream&, const std::string& indent) override;
    };
    
    class ModuleDict: public Module {
        public:
            ModuleDict();
            ModuleDict(std::initializer_list<std::pair<std::string, ModuleP&&>>);

            cml::Tensor forward(const cml::Tensor&) override;

            std::ostream& print(std::ostream&, const std::string& indent) override;
    };

}
}

#endif // __CML_NN_CONTAINERS_H__
