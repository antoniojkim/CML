#include "../Loss.h"
#include "../../Functions/Loss/MSELoss.h"

using namespace std;
using namespace cml;
using namespace cml::nn;


/***********************************************************************************
********************************* Constructors *************************************
************************************************************************************/

template<typename T>
MSELoss<T>::MSELoss(const Reduction& reduction): reduction{reduction} {}


/***********************************************************************************
*********************************** Methods ****************************************
************************************************************************************/


template<typename T>
cml::tensor<T> MSELoss<T>::forward(cml::tensor<T> actual, cml::tensor<T> expected){
    return Function::MSELoss::forward(actual, expected, reduction);
}


/***********************************************************************************
**************************** Template Instantiations *******************************
************************************************************************************/

INSTANTIATE_CLASS_TEMPLATES(MSELoss);


