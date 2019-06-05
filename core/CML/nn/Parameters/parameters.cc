
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



/***********************************************************************************
*********************************** Methods ****************************************
************************************************************************************/

template<typename T> 
cml::Tensor<T>& Parameter<T>::toTensor(){
    return static_cast<cml::Tensor<T>&>(*this);
}

template<typename T> 
Parameter<T>& Parameter<T>::operator+=(const T& gradient){
    this->gradient += gradient;
    return *this;
}
template<typename T> 
void Parameter<T>::zeroGrad(){
    this->gradient = (T)(0);
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

INSTANTIATE_CLASS_TEMPLATES(Parameter);
INSTANTIATE_CLASS_TEMPLATES(Parameters);


