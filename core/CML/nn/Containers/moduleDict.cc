
#include "../Containers.h"
#include "../../Dtypes.h"

using namespace std;
using namespace cml;
using namespace cml::nn;

/***********************************************************************************
********************************* Constructors *************************************
************************************************************************************/

template<typename T>
ModuleDict<T>::ModuleDict() {}
template<typename T>
ModuleDict<T>::ModuleDict(initializer_list<pair<string, Module<T>*>> dict): Module<T>{dict} {}



/***********************************************************************************
*********************************** Methods ****************************************
************************************************************************************/

template<typename T>
tensor<T> ModuleDict<T>::forward(tensor<T> x) {
    auto y = x;
    for (auto& submodule : submodules){
        y = (*submodule)(y);
    }
    return y;
}

template<typename T>
ostream& ModuleDict<T>::print(ostream& out, const string& indent){
    out << "ModuleDict {" << endl;
    for (auto& submodule : submodules){
        out << indent << "    " << mValues[submodule.get()] << ":  ";
        submodule->print(out, indent+"    ") << endl;
    }
    out << indent << "}";
    return out;
}



/***********************************************************************************
**************************** Template Instantiations *******************************
************************************************************************************/

INSTANTIATE_CLASS_TEMPLATES(ModuleDict);