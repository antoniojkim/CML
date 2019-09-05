
#include <iostream>
#include <memory>
#include <vector>


using namespace std;

#include <Eigen/Core>
#include <unsupported/Eigen/CXX11/Tensor>

#include "../../core/Utils/TypeName.h"

template <typename T>
using DMatrix = Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>;  // Dynamic Matrix

template<typename T, int nDims>
auto to_matrix(Eigen::Tensor<T, nDims>& t){
    auto R = t.dimension(0);
    auto C = t.size() / R;
    return Eigen::Map<DMatrix<T>>(t.data(), R, C);
}

int main(){


    DMatrix<double> m1 {3, 3};
    m1 << 1, 2, 3, 4, 5, 6, 7, 8, 9;

    cout << m1 << endl << endl;

    cout << m1.sum() << endl << endl;

    cout << "Colwise:" << endl;
    cout << m1.colwise().sum() << endl << endl;

    cout << "Rowwise:" << endl;
    cout << m1.rowwise().sum() << endl << endl;

    cout << "-----------------------------------------------------------------" << endl << endl;


    DMatrix<double> m2 {3, 3};
    m2 << 10, 11, 12, 13, 14, 15, 16, 17, 18;

    cout << m2 << endl << endl;

    cout << m2.array().exp().colwise().sum().log() << endl << endl;

    cout << (m1.rowwise() - static_cast<DMatrix<double>>(m2.array().exp().colwise().sum().log()).row(0)) << endl << endl;
    
}
