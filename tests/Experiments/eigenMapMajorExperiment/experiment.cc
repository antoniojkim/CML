
#include <iostream>
#include <memory>
#include <type_traits>

using namespace std;

#include "../../../core/CML/Tensor.h"

template <typename T>
using DMatrix = Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>;  // Dynamic Matrix

int main(){

    auto t = cml::make_tensor<int, 3, 2>({
        {1, 2}, {3, 4}, {5, 6}
    });
    t->print(cout) << endl;;
    cout << t->matrix() << endl;

    // int* a = new int[6];
    // for (int i = 0; i < 6; ++i){ a[i] = i+1; }

    // auto m = Eigen::Map<DMatrix<int>>(a, 3, 2);
    // cout << m << endl << endl;

}
