
#include <iostream>
#include <memory>
#include <vector>


using namespace std;

#include <Eigen/Core>
#include <unsupported/Eigen/CXX11/Tensor>

#include "../../core/Utils/TypeName.h"

template <typename T>
using DMatrix = Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>;  // Dynamic Matrix

template<typename T>
struct TensorBase {

    virtual T* data() = 0;
    
    virtual int numDims() = 0;
    virtual vector<int> dims() = 0;
    
};

template <typename T>
using tensor = std::shared_ptr<TensorBase<T>>;

template<typename T, int nDims>
struct Tensor: public TensorBase<T> {
    
    Eigen::Tensor<T, nDims> t;
    
    template<typename... Dims>
    Tensor(Dims... dims): t(dims...) {
        t.setRandom();
    }
    
    Eigen::Map<DMatrix<T>> matrix(){
        auto R = t.dimension(0);
        auto C = t.size() / R;
        return Eigen::Map<DMatrix<T>>(t.data(), R, C);
    }
    T* data() override { return t.data(); }
    
    int numDims() override {
        return t.NumDimensions;
    }
    vector<int> dims() override {
        auto d = t.dimensions();
        return vector<int>(std::begin(d), std::end(d));
    }
    
};

template<typename T, typename... Dims>
tensor<T> make_tensor(Dims... dims){
    return std::make_shared<Tensor<T, 2>>(dims...);
}

template<typename T>
auto extract_tensor(tensor<T> t){
    switch(t->numDims()){
        case 2:
            return static_pointer_cast<std::shared_ptr<Tensor<T, 2>>>(t);
        case 3:
            return static_pointer_cast<std::shared_ptr<Tensor<T, 3>>>(t);
        default:
            throw "Invalid number of dimensions";
    }
}

template<typename T>
ostream& operator<<(ostream& out, const vector<T>& v){
    out << "{ ";
    for (auto& e : v){
        out << e << " ";
    }
    out << "}";
    return out;
}

int main(){
    auto t = make_tensor<double>(2, 2);
    
    cout << t->numDims() << endl;
    cout << t->dims() << endl;
    
    auto t2 = Eigen::TensorMap
    
//     auto m = extract_tensor(t);
    
//     cout << m->matrix() << endl;
    
}
