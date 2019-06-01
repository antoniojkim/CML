
#include "../Containers.h"
#include "../../Dtypes.h"

using namespace std;
using namespace cml;
using namespace cml::nn;

/***********************************************************************************
********************************* Constructors *************************************
************************************************************************************/

template<typename T>
ModuleList<T>::ModuleList() {}
template<typename T>
ModuleList<T>::ModuleList(std::initializer_list<Module<T>*> submodules): Module<T>{submodules} {}



/***********************************************************************************
*********************************** Methods ****************************************
************************************************************************************/

template<typename T>
Tensor<T> ModuleList<T>::forward(Tensor<T>& x) {
    auto y = x;
    for (auto& submodule : submodules){
        y = (*submodule)(y);
    }
    return y;
}

template<typename T>
std::ostream& ModuleList<T>::print(std::ostream& out, const std::string& indent){
    out << indent << "ModuleList {" << endl;
    for (auto& submodule : submodules){
        out << indent << "    ";
        submodule->print(out, indent+"    ") << endl;
    }
    out << indent << "}";
    return out;
}


/***********************************************************************************
**************************** Template Instantiations *******************************
************************************************************************************/

INSTANTIATE_CLASS_TEMPLATES(ModuleList);
