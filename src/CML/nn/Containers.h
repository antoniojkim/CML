#ifndef __CML_NN_CONTAINERS_H__
#define __CML_NN_CONTAINERS_H__

#include "Modules.h"
#include "../Tensor.h"

#include <string>
#include <utility>

namespace cml {
namespace nn {
    
    template<typename T = float>
    class Sequential: public Module<T> {
        using Module<T>::submodules;
        using Module<T>::keys;

        public:
            Sequential();
            Sequential(std::initializer_list<Module<T>*> submodules);
            Sequential(std::initializer_list<std::pair<std::string, Module<T>*>>);

            cml::Tensor<T> forward(const cml::Tensor<T>&) override;

            std::ostream& print(std::ostream&, const std::string& indent) override;
    };
    
    template<typename T = float>
    class ModuleList: public Module<T> {
        using Module<T>::submodules;

        public:
            ModuleList();
            ModuleList(std::initializer_list<Module<T>*> submodules);

            cml::Tensor<T> forward(const cml::Tensor<T>&) override;

            std::ostream& print(std::ostream&, const std::string& indent) override;
    };
    
    template<typename T = float>
    class ModuleDict: public Module<T> {
        using Module<T>::submodules;
        using Module<T>::keys;

        public:
            ModuleDict();
            ModuleDict(std::initializer_list<std::pair<std::string, Module<T>*>>);

            cml::Tensor<T> forward(const cml::Tensor<T>&) override;

            std::ostream& print(std::ostream&, const std::string& indent) override;
    };

}
}

#endif // __CML_NN_CONTAINERS_H__
