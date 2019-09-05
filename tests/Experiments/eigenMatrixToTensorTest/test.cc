
#include <iostream>

using namespace std;

#include <Eigen/Core>
#include <unsupported/Eigen/CXX11/Tensor>

#include "../../core/Utils/TypeName.h"

template <typename T>
using DMatrix = Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>;  // Dynamic Matrix

template<typename T, int nDims>
struct Tensor {
    
    Eigen::Tensor<T, nDims> t;
    
    template<typename... Dims>
    Tensor(Dims... dims): t(dims...) {}
    
    Eigen::Map<DMatrix<T>> matrix(){
        auto R = t.dimension(0);
        auto C = t.size() / R;
        return Eigen::Map<DMatrix<T>>(t.data(), R, C);
    }
    
    Tensor<T, nDims>& set(DMatrix<T>&& m){
        t = std::move(Eigen::TensorMap<Eigen::Tensor<const T, 2>>(matrix.data(), {matrix.rows(), matrix.cols()}));
        return *this;
    }
    
};

template<typename T>
void print(const Eigen::MatrixBase<T>& m){
    cout << m << endl << endl;
}

// template<typename T, typename... Dims>
// auto Matrix_to_Tensor(const DMatrix<T>& matrix, Dims... dims){
//     constexpr int rank = sizeof... (Dims);
//     return Eigen::TensorMap<Eigen::Tensor<const T, rank>>(matrix.data(), {dims...});
// }
template<typename T>
auto Matrix_to_Tensor(DMatrix<T>&& matrix){
    return std::move(Eigen::TensorMap<Eigen::Tensor<const T, 2>>(matrix.data(), {matrix.rows(), matrix.cols()}));
}

int main(){
    
    Tensor<double, 2> t1 {2, 2};
    t1.t.setRandom();
    cout << t1.t << endl << endl;
    
    Tensor<double, 2> t2 {2, 2};
    t2.t.setRandom();
    cout << t2.t << endl << endl;
    
    Tensor<double, 2> t3 {2, 2};
    t3.t.setRandom();
    cout << t3.t << endl << endl;
    
    auto p = static_cast<DMatrix<double>>(t1.matrix() * t2.matrix());
    cout << &p(0, 0) << endl;
    print(p);
    
    cout << type_name<decltype(t1.matrix() * t2.matrix())>() << endl << endl;
    
    t3.t = Matrix_to_Tensor(std::move(p));
    
//     t3 = t1.matrix() * t2.matrix();
    cout << &t3.t(0, 0) << endl;
    cout << t3.t << endl << endl;
    
    cout << type_name<decltype(t1.matrix().transpose())>() << endl << endl;
    
    
}
