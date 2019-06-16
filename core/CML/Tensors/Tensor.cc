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

// template<typename T>
// Tensor<T>::Tensor(tensor<T> t): DMatrix<T>{t->data()}, computeGrad{t->computeGrad} {}
// template<typename T>
// Tensor<T>::Tensor(Tensor<T>& t): DMatrix<T>{t.data()}, computeGrad{t.computeGrad} {}
template<typename T>
Tensor<T>::Tensor(Tensor<T>&& t): DMatrix<T>{std::move(t.data())}, dcg{std::move(t.dcg)}, computeGrad{t.computeGrad} {}
template<typename T>
Tensor<T>::Tensor(DMatrix<T>& m): DMatrix<T>{m} {}
template<typename T>
Tensor<T>::Tensor(DMatrix<T>&& m): DMatrix<T>{std::move(m)} {}

template<typename T>
Tensor<T>::Tensor(std::initializer_list<T> data, const bool& computeGrad): 
        DMatrix<T>{data.size(), 1},
        computeGrad{computeGrad} {
// #ifdef DEBUG
//     cout << "Initialized 1d data" << endl;
// #endif
    unsigned int i = 0;
    for (auto& e : data){
        this->data()(i, 0) = e;
        ++i;
    }
}
template<typename T>
Tensor<T>::Tensor(std::initializer_list<std::initializer_list<T>> data, const bool& computeGrad): 
        DMatrix<T>{data.size(), data.begin()->size()},
        computeGrad{computeGrad} {
// #ifdef DEBUG
//     cout << "Initialized 2d data" << endl;
// #endif
    unsigned int i, j;

    i = 0;
    for (auto& row : data){
        j = 0;
        for (auto& e : row){
            this->data()(i, j) = e;
            ++j;
        }
        ++i;
    }
}
template<typename T>
Tensor<T>::Tensor(const int& R, const int& C, const bool& computeGrad): 
        DMatrix<T>{std::move(DMatrix<T>::Zero(R, C))}, 
        computeGrad{computeGrad} {
// #ifdef DEBUG
//     cout << "Initialized R and C" << endl;
// #endif
}


// template<typename T>
// Tensor<T>& Tensor<T>::operator=(Tensor<T>& t){
//     if (t.rows() != this->rows() || t.cols() != this->cols()){
//         this->data().resize(t.rows(), t.cols());
//     }
//     this->data() = t.data();
//     return *this;
// }
// template<typename T>
// Tensor<T>& Tensor<T>::operator=(Tensor<T>&& t){
//     if (t.rows() != this->rows() || t.cols() != this->cols()){
//         this->data().resize(t.rows(), t.cols());
//     }
//     this->data() = std::move(t.data());
//     this->dcg = std::move(t.dcg);
//     return *this;
// }



/***********************************************************************************
*********************************** Methods ****************************************
************************************************************************************/

template<typename T>
DMatrix<T>& Tensor<T>::data(){
    return static_cast<DMatrix<T>&>(*this);
}
template<typename T>
T& Tensor<T>::data(const int& R, const int& C){
    return data()(R, C);
}

template<typename T>
vector<long int> Tensor<T>::shape(){ return {this->rows(), this->cols()}; }
template<typename T>
std::ostream& Tensor<T>::info(std::ostream& out){
    return out << "{" << this->rows() << ", " << this->cols() << "}";
}


template<typename T>
void Tensor<T>::fill(const T& coefficient){
    data() = DMatrix<T>::Constant(this->rows(), this->cols(), coefficient);
}
template<typename T>
void Tensor<T>::zero(){
    data() = DMatrix<T>::Zero(this->rows(), this->cols());
}


template<typename T>
void Tensor<T>::randomize(Randomizer::Function<T> randomizer){
    data() = data().unaryExpr(randomizer);
}
template<typename T>
void Tensor<T>::randomize(const T& coefficient){
//     data() = data().unaryExpr([coefficient](T x) -> T { return (T)(gauss(e2) * coefficient); });
}

template<typename T>
void Tensor<T>::readIDX(std::istream& in, const bool& readMagic){
    // if (readMagic){
    //     int 
    // }
}


template<typename T>
void Tensor<T>::initGraph(std::vector<tensor<T>> params, GradientFunction<T> f){
    if (!dcg){
        dcg = make_unique<DCG<T>>(this, std::forward<std::vector<tensor<T>>>(params), 
                                        std::forward<GradientFunction<T>>(f));
    }
    else{
        throw "Called initGraph when graph already exists";
    }
}

template<typename T>
std::unique_ptr<DCG<T>>& Tensor<T>::graph(){
    if (!dcg){
        if (computeGrad){
            initGraph();
        }
        else{
            throw "Getting graph of tensor with computeGrad == false";
        }
    }
    return dcg;
}
 
template<typename T>
void Tensor<T>::backward(){
    if (this->rows() != 1 || this->cols() != 1){
        throw "backward can only be called on a scalar tensor";
    }
#ifdef DEBUG
    cout << "Calling backward on a scalar tensor" << endl;
#endif
    graph()->backward();
}



/***********************************************************************************
**************************** Template Instantiations *******************************
************************************************************************************/

INSTANTIATE_CLASS_TEMPLATES(Tensor);

