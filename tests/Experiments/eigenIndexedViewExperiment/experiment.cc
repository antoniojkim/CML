
#include <iostream>
#include <memory>

using namespace std;

#include <Eigen/Core>
#include <unsupported/Eigen/CXX11/Tensor>

// #include "../../../core/CML/Tensor.h"

template <typename T>
using DMatrix = Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>;  // Dynamic Matrix

int main(){

    DMatrix<float> m1{2, 2};
    m1 << 1, 3, 2, 4;

    cout << m1 << endl << endl;

    DMatrix<float> p = m1.rowwise() - static_cast<DMatrix<float>>(m1.array().exp().colwise().sum().log()).row(0);

    cout << p << endl << endl;

    float t = 0;
    t -= p(0, 0);

    cout << t << endl << endl;

    auto d = shared_ptr<float>(new float[4], default_delete<float[]>());
    for (int i = 0; i<4; ++i){
        d.get()[i] = i+1;
    }
    auto m2 = Eigen::Map<DMatrix<float>>(d.get(), 2, 2);

    cout << &d.get()[0] << endl;
    cout << &m2(0, 0) << endl;

    cout << m2 << endl << endl;

    DMatrix<float> p2 = m2.rowwise() - static_cast<DMatrix<float>>(m2.array().exp().colwise().sum().log()).row(0);

    cout << p2 << endl << endl;

    float t2 = 0;
    t2 -= p2(0, 0);

    cout << t2 << endl;



}
