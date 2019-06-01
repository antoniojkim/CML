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
Tensor<T>::Tensor(const int& R): DMatrix<T>{R, 1}, R{R}, C{1} {}
template<typename T>
Tensor<T>::Tensor(const int& R, const int& C): DMatrix<T>{R, C}, R{R}, C{C} {}

template<typename T>
Tensor<T>::~Tensor(){
    if (graph) delete graph;
}


template<typename T>
Tensor<T>& Tensor<T>::operator=(Tensor<T>& scalar){
    if (scalar.rows() != R || scalar.cols() != C){
        this->data().resize(scalar.rows(), scalar.cols());
    }
    this->data() = std::move(scalar.data());
    return *this;
}
template<typename T>
Tensor<T>& Tensor<T>::operator=(Tensor<T>&& scalar){
    if (scalar.rows() != R || scalar.cols() != C){
        this->data().resize(scalar.rows(), scalar.cols());
    }
    this->data() = std::move(scalar.data());
    return *this;
}



/***********************************************************************************
*********************************** Methods ****************************************
************************************************************************************/

template<typename T>
DMatrix<T>& Tensor<T>::data(){
    return static_cast<DMatrix<T>&>(*this);
}
template<typename T>
long int Tensor<T>::rows(){ return R; }
template<typename T>
long int Tensor<T>::cols(){ return C; }


template<typename T>
void Tensor<T>::fill(const T& coefficient){
    data() = DMatrix<T>::Constant(R, C, coefficient);
}


/***********************************************************************************
****************************** Arithmetic Methods **********************************
************************************************************************************/

// template<typename T>
// Tensor<T> Tensor<T>::operator+(const T& scalar){
//     auto t = Tensor<T>(static_cast<DMatrix<T>>(this->data() + scalar));
//     t.graph = new DCG<T>(this->graph);
//     t.graph->f = [](Tensor<T>& output) -> Tensor<T> {
//         Tensor<T> t (1, 1);
//         t << (T)(1);
//         return t;
//     };
//     return t;
// }

// template<typename T>
// Tensor<T> Tensor<T>::operator-(const T& scalar){
//     auto t = Tensor<T>(static_cast<DMatrix<T>>(this->data() - scalar));
//     t.graph = new DCG<T>(this->graph);
//     t.graph->f = [](Tensor<T>& output) -> Tensor<T> {
//         Tensor<T> t (1, 1);
//         t << (T)(-1);
//         return t;
//     };
//     return t;
// }

template<typename T>
Tensor<T> Tensor<T>::operator*(const T& scalar){
    auto t = Tensor<T>(static_cast<DMatrix<T>>(this->data() * scalar));
    t.graph = new DCG<T>(this->graph);
    t.graph->f = [scalar](Tensor<T>& output) -> Tensor<T> {
        Tensor<T> t (1, 1);
        t << scalar;
        return t;
    };
    return t;
}


/***********************************************************************************
**************************** Template Instantiations *******************************
************************************************************************************/

INSTANTIATE_CLASS_TEMPLATES(Tensor);

