
#include <iostream>
#include <memory>
#include <vector>
#include <ostream>


using namespace std;

#include <Eigen/Core>
#include <unsupported/Eigen/CXX11/Tensor>

#include "../../core/Utils/TypeName.h"

template<typename T>
ostream& operator<<(ostream& out, vector<T> v){
    out << "[";
    for(auto& e : v){
        out << e << ", ";
    }
    out << "]";
    return out;
}

int main(){
    int a[12] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

    vector<int> v1 = {3, 4};
    vector<int> v2 = {2, 2, 3};

    // cout << v1 << endl;
    // cout << v2 << endl;

    std::array<int, 2> arr1;
    std::copy_n(v1.begin(), 2, arr1.begin());

    auto t1 = Eigen::TensorMap<Eigen::Tensor<int, 2>>((int*)(&a), arr1);
    cout << t1 << endl;

    
    std::array<int, 3> arr2;
    std::copy_n(v2.begin(), 3, arr2.begin());

    auto t2 = Eigen::TensorMap<Eigen::Tensor<int, 3>>((int*)(&a), arr2);
    cout << t2 << endl;

    // Eigen::TensorMap
}
