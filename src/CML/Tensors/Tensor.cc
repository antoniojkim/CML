#ifdef DEBUG
#include <iostream>
#endif

#include "../Tensor.h"
#include "../DCG.h"
#include "../Dtypes.h"

using namespace std;
using namespace cml;
using namespace Eigen;


/***********************************************************************************
********************************* Constructors *************************************
************************************************************************************/

template<typename T>
Tensor<T>::Tensor(const int& R): DMatrix<T>{R, 1} {}
template<typename T>
Tensor<T>::Tensor(const int& R, const int& C): DMatrix<T>{R, C} {}
// Tensor(const int& R, const int& C, const int& D);



/***********************************************************************************
*********************************** Methods ****************************************
************************************************************************************/

template<typename T>
DMatrix<T>& Tensor<T>::data(){
    return static_cast<DMatrix<T>&>(*this);
}


/***********************************************************************************
****************************** Arithmetic Methods **********************************
************************************************************************************/

template<typename T>
Tensor<T> Tensor<T>::operator*(const long long& scalar){
    auto t = Tensor<T>(static_cast<DMatrix<T>>(this->data() * scalar));
    t.graph = new DCG<T>(this->graph);
    t.graph->f = [scalar](Tensor<T>& output) -> Tensor<T> {
        return output;
    };
    delete t.graph;
    t.graph = nullptr;
    return t;
}


/***********************************************************************************
**************************** Template Instantiations *******************************
************************************************************************************/

INSTANTIATE_CLASS_TEMPLATES(Tensor);

