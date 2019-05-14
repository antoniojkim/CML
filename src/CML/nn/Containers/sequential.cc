
#include "../Containers.h"
#include "../../Dtypes.h"

using namespace std;
using namespace cml;
using namespace cml::nn;

/***********************************************************************************
********************************* Constructors *************************************
************************************************************************************/

template<typename T>
Sequential<T>::Sequential() {}
template<typename T> template<typename ...U>
Sequential<T>::Sequential(U&&...submodules): Module<T>(std::forward<T>(submodules)...) {}
template<typename T>
Sequential<T>::Sequential(initializer_list<pair<string, uModule<T>&&>> dict): Module<T>{dict} {}



/***********************************************************************************
*********************************** Methods ****************************************
************************************************************************************/

template<typename T>
Tensor<T> Sequential<T>::forward(const Tensor<T>& x) {
    auto y = x;
    for (auto& submodule : submodules){
        y = (*submodule)(y);
    }
    return y;
}

template<typename T>
ostream& Sequential<T>::print(ostream& out, const string& indent){
    out << "Sequential {" << endl;
    for (auto& submodule: submodules){
        out << indent << "    ";
        if (keys.count(&submodule) > 0){
            out << keys[&submodule] << ":  ";
        }
        submodule->print(out, indent+"    ") << endl;
    }
    out << indent << "}";
    return out;
}



/***********************************************************************************
**************************** Template Instantiations *******************************
************************************************************************************/

INSTANTIATE_TEMPLATES(Sequential);
