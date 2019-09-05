
#include <cassert>
#include <functional>
#include <iostream>
#include <memory>
#include <vector>
#include <ostream>

#include <initializer_list>


using namespace std;

#include <Eigen/Core>
#include <unsupported/Eigen/CXX11/Tensor>

template<typename T>
class A {
    T t;
    
    protected:
    
        A(const T& t): t{t} {}
    
    public:
        T& getT(){ return t; }
    
        template<int N>
        static shared_ptr<A<T>> make_a(const T& t){
            return make_shared<A<T>>(t+N);
        }
};

template<typename T, int N>
shared_ptr<A<T>> make_A(const T& t){
    return A<T>::template make_a<N>(t);
}

// template <typename T>
// void use_function(T t) {
//   typedef std::function<T(T,T)> Funcp = func<T>;
//   // use Funcp here
// }

// template<typename T, int N>
// function<shared_ptr<A<T>>(const T&)> functionA = A<T>::make_a<N>;

int main(){
//     functionA<float, 2>(3);
//     auto a = A<float>::make_a<2>(3); // This works
    auto a = make_A<int, 2>(3); // This works now
    cout << a.get() << endl;
    cout << a->getT() << endl;
}
