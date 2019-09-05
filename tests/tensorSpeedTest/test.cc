
#include <ctime>
#include <functional>
#include <iostream>
using namespace std;

#include <Eigen/Core>
#include <unsupported/Eigen/CXX11/Tensor>

#include "../../core/Utils/TypeName.h"


template <typename T>
using DMatrix = Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>;  // Dynamic Matrix

template<typename T>
struct Tensor1 {
    int R, C;
    DMatrix<T> m;

    Tensor1(const int& R, const int& C): R{R}, C{C}, m{R, C} {}

    DMatrix<T>& data(){ return m; }
};

template<typename T>
struct Tensor2 {
    int R, C;
    Eigen::Tensor<T, 2> t;

    Tensor2(const int& R, const int& C): R{R}, C{C}, t{R, C} {}

    inline auto matrix(){ return Eigen::Map<DMatrix<T>>(t.data(), R, C); }
    Eigen::Tensor<T, 2>& data(){ return t; }


    Tensor2<T>& set(std::initializer_list<std::initializer_list<T>> values) {
        t.setValues(std::forward<std::initializer_list<std::initializer_list<T>>>(values));
        return *this;
    }
    // template<template<typename> typename List>
    // T& set(std::initializer_list<List<T>> values) {
    //     t.setValues(std::forward<std::initializer_list<List<T>>>(values));
    // }
};

int R = 64;
int C = 128;

int numTrials = 100;
int trialLength = 10000;

void testTensor1(){


    Tensor1<double> t11 {R, C};
    Tensor1<double> t12 {C, R};
    Tensor1<double> t13 {R, R};


    clock_t start = clock();
    clock_t end = clock();

    double totalTime = 0;

    for (int trial = 0; trial < numTrials; ++trial){
        t11.data().setRandom();
        t12.data().setRandom();
        start = clock();
        for (int i = 0; i < trialLength; ++i){
            t13.data() = t11.data() * t12.data();
        }
        end = clock();
        totalTime += double(end-start)/CLOCKS_PER_SEC;
    }

    double averageTime = totalTime / numTrials;

    cout << "Took " << averageTime << " seconds on average" << endl;

}

void testTensor2(){

    Tensor2<double> t11 {R, C};
    Tensor2<double> t12 {C, R};
    Tensor2<double> t13 {R, R};


    clock_t start = clock();
    clock_t end = clock();

    double totalTime = 0;

    for (int trial = 0; trial < numTrials; ++trial){
        t11.data().setRandom();
        t12.data().setRandom();
        start = clock();
        for (int i = 0; i < trialLength; ++i){
            t13.matrix() = t11.matrix() * t12.matrix();
        }
        end = clock();
        totalTime += double(end-start)/CLOCKS_PER_SEC;
    }

    double averageTime = totalTime / numTrials;

    cout << "Took " << averageTime << " seconds on average" << endl;

}

int main (){
    // cout << "Testing Eigen Tensor Performance" << endl;

    // testTensor1();
    // testTensor2();
    // cout << endl;

    // testTensor1();
    // testTensor2();

    Tensor2<double> t {2, 2};
    t.data().setZero();
    // cout << type_name<decltype(t11.matrix())>() << endl;
    // cout << type_name<decltype(t11.data())>() << endl;
    // cout << sizeof(t11) << endl;
    // cout << sizeof(t11.matrix()) << endl;
    // cout << sizeof(t11.data()) << endl;

    cout << t.data() << endl;
    // t.set({1, 2, 3, 4});
    t.set({{1, 2}, {3, 4}});
    cout << t.data() << endl;


    /*
        Conclusion, using the unsupported Tensor Type isn't any slower than using the supported matrix type.
        In light of this, I may change the tensor class one more time to just use the unsupported tensor type.
     */

}