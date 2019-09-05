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
        using Module<T>::mValues;
        using Module<T>::pKeys;

        public:
            Sequential(): Module<T>{} {}
            Sequential(std::initializer_list<Module<T>*> submodules): Module<T>{submodules} {}
            Sequential(std::initializer_list<std::pair<std::string, Module<T>*>> dict): Module<T>{dict} {}

            cml::tensor<T> forward(cml::tensor<T> x) override {
                auto y = x;
                for (auto& submodule : submodules){
                    y = (*submodule)(y);
                }
                return y;
            }

            std::ostream& print(std::ostream& out, const std::string& indent) override {
                using namespace std;
                out << "Sequential {" << endl;
                for (auto& submodule: submodules){
                    out << indent << "    ";
                    if (mValues.count(submodule.get()) > 0){
                        out << mValues[submodule.get()] << ":  ";
                    }
                    submodule->print(out, indent+"    ") << endl;
                }
                out << indent << "}";
                return out;
            }

    };

/*
    // Commented out as they are too similar to Sequential

    template<typename T = float>
    class ModuleList: public Module<T> {
        using Module<T>::submodules;

        public:
            ModuleList(): Module<T>{} {}
            ModuleList(std::initializer_list<Module<T>*> submodules): Module<T>{submodules} {}

            cml::tensor<T> forward(cml::tensor<T> x) override {
                auto y = x;
                for (auto& submodule : submodules){
                    y = (*submodule)(y);
                }
                return y;
            }

            std::ostream& print(std::ostream& out, const std::string& indent) override {
                using namespace std;
                out << indent << "ModuleList {" << endl;
                for (auto& submodule : submodules){
                    out << indent << "    ";
                    submodule->print(out, indent+"    ") << endl;
                }
                out << indent << "}";
                return out;
            }
    };

    template<typename T = float>
    class ModuleDict: public Module<T> {
        using Module<T>::submodules;
        using Module<T>::mValues;

        public:
            ModuleDict(): Module<T>{} {}
            ModuleDict(std::initializer_list<std::pair<std::string, Module<T>*>> dict): Module<T>{dict} {}

            cml::tensor<T> forward(cml::tensor<T> x) override  {
                auto y = x;
                for (auto& submodule : submodules){
                    y = (*submodule)(y);
                }
                return y;
            }

            std::ostream& print(std::ostream& out, const std::string& indent) override {
                using namespace std;
                out << "ModuleDict {" << endl;
                for (auto& submodule : submodules){
                    out << indent << "    " << mValues[submodule.get()] << ":  ";
                    submodule->print(out, indent+"    ") << endl;
                }
                out << indent << "}";
                return out;
            }
    };
*/

}
}

#endif // __CML_NN_CONTAINERS_H__
