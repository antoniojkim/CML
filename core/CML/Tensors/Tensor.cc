#ifdef DEBUG
#include <iostream>
#endif

#include <random>

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
Tensor<T>::Tensor(tensor<T> t): DMatrix<T>{t->data()}, R{t->rows()}, C{t->cols()}, graph{t->graph} {}
template<typename T>
Tensor<T>::Tensor(Tensor<T>& t): DMatrix<T>{t.data()}, R{t.rows()}, C{t.cols()}, graph{t.graph} {}
template<typename T>
Tensor<T>::Tensor(Tensor<T>&& t): DMatrix<T>{std::move(t.data())}, R{t.rows()}, C{t.cols()}, graph{t.graph} {}
template<typename T>
Tensor<T>::Tensor(DMatrix<T>& m): DMatrix<T>{m}, R{m.rows()}, C{m.cols()} {}
template<typename T>
Tensor<T>::Tensor(DMatrix<T>&& m): DMatrix<T>{std::move(m)}, R{m.rows()}, C{m.cols()} {}

template<typename T>
Tensor<T>::Tensor(const int& R): DMatrix<T>{std::move(DMatrix<T>::Zero(R, 1))}, R{R}, C{1} {}
template<typename T>
Tensor<T>::Tensor(const int& R, const int& C): DMatrix<T>{std::move(DMatrix<T>::Zero(R, C))}, R{R}, C{C} {}

template<typename T>
Tensor<T>::~Tensor(){}


template<typename T>
Tensor<T>& Tensor<T>::operator=(Tensor<T>& t){
    if (t.rows() != R || t.cols() != C){
        this->data().resize(t.rows(), t.cols());
    }
    this->data() = t.data();
    this->graph = t.graph;
    t.graph = nullptr;
    return *this;
}
template<typename T>
Tensor<T>& Tensor<T>::operator=(Tensor<T>&& t){
    if (t.rows() != R || t.cols() != C){
        this->data().resize(t.rows(), t.cols());
    }
    this->data() = std::move(t.data());
    this->graph = t.graph;
    t.graph = nullptr;
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
template<typename T>
void Tensor<T>::zero(){
    data() = DMatrix<T>::Zero(R, C);
}


std::random_device rd;
std::mt19937 e2(rd());
std::normal_distribution<> gauss(0, 1);

template<typename T>
void Tensor<T>::randomize(){
    data() = data().unaryExpr([](T x) -> T { return (T)gauss(e2); });
}
template<typename T>
void Tensor<T>::randomize(const T& coefficient){
    data() = data().unaryExpr([coefficient](T x) -> T { return (T)(gauss(e2) * coefficient); });
}

template<typename T>
void Tensor<T>::readIDX(std::istream& in, const bool& readMagic){
    // if (readMagic){
    //     int 
    // }
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
tensor<T> Tensor<T>::operator*(const T& scalar){
    auto t = make_tensor<T>(static_cast<DMatrix<T>>(
        this->data() * scalar
    ));
    t->graph = make_graph<T>(this->graph);
    t->graph->f = [scalar](tensor<T> output) -> tensor<T> {
        auto u = make_tensor<T>(1, 1);
        (*u) << scalar;
        return u;
    };
    return t;
}


/***********************************************************************************
**************************** Template Instantiations *******************************
************************************************************************************/

INSTANTIATE_CLASS_TEMPLATES(Tensor);

