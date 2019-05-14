
#include "../Parameter.h"
#include "../../Dtypes.h"

using namespace std;
using namespace cml::nn;

/***********************************************************************************
******************************** Parameter Class ***********************************
************************************************************************************/

/***********************************************************************************
********************************* Constructors *************************************
************************************************************************************/

template<typename T>
Parameter<T>::Parameter(Parameter<T>& p): cml::Tensor<T>(std::move(p.toTensor())) {}

template<typename T> template<typename...Args>
Parameter<T>::Parameter(Args&&... args): cml::Tensor<T>(std::forward<Args>(args)...) {}



/***********************************************************************************
*********************************** Methods ****************************************
************************************************************************************/

template<typename T> template<class U>
uParameter<U> Parameter<T>::to(){
    return std::make_unique<Parameter<U>>(this);
}

template<typename T> 
cml::Tensor<T>& Parameter<T>::toTensor(){
    return static_cast<cml::Tensor<T>&>(*this);
}

template<typename T>
std::ostream& operator<<(std::ostream& out, Parameter<T>& p){
    return out << static_cast<cml::Tensor<T>&>(p);
}



/***********************************************************************************
******************************** Parameters Class **********************************
************************************************************************************/

template<typename T>
void Parameters<T>::emplace_back(uParameter<T>&& p, const std::string& key){ add(std::move(p), key); }
template<typename T>
void Parameters<T>::push_back(uParameter<T>&& p, const std::string& key){ add(std::move(p), key); }
template<typename T>
void Parameters<T>::append(uParameter<T>&& p, const std::string& key){ add(std::move(p), key); }
template<typename T>
void Parameters<T>::add(uParameter<T>&& p, const std::string& key){
    params.emplace_back(std::move(p));
    if (key != "") { values[key] = params.back().get(); };
}


template<typename T>
Parameter<T>& Parameters<T>::operator[](const int& index){
    if (index >= 0 && index < (int) params.size()){
        return *params[index];
    }
    else if (index < 0 && -index <= (int) params.size()){
        return *params[params.size()+index];
    }

    std::ostringstream error;
    error << "Invalid index: " << index << ",  params.size() == " << params.size();
    throw error.str();
}
template<typename T>
Parameter<T>& Parameters<T>::operator[](const std::string& key){
    if (values.count(key) > 0){  return *values[key];  }
    
    std::ostringstream error;
    error << "Invalid key: " << key;
    throw error.str();
}


/***********************************************************************************
**************************** Template Instantiations *******************************
************************************************************************************/

INSTANTIATE_TEMPLATES(Parameter);
INSTANTIATE_TEMPLATES(Parameters);


