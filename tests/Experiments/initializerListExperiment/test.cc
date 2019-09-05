
#include <cassert>
#include <iostream>
#include <memory>
#include <vector>
#include <ostream>

#include <initializer_list>


using namespace std;

#include <Eigen/Core>
#include <unsupported/Eigen/CXX11/Tensor>

#include "../../core/Utils/TypeName.h"
#include "../../core/Utils/VectorUtils.h"

struct A {
    vector<int> v;
    
    int operator[](initializer_list<int> i){
        int sum = 0;
        for(auto& e : i){
            if (e < v.size()){
                sum += v[e];
            }
        }
        return sum;
    }
};

void test1(){
    A a;
    for (int i = 1; i<10; ++i){
        a.v.emplace_back(i);
    }

    auto sum = a[{1, 2, 3}];

    assert(sum == 9);
}


template<typename T>
struct B {
    vector<T> v;
    size_t prod;

    B() {}
    B(vector<T>&& v): v{std::move(v)} {}

    template<T... args>
    void set(){
        v = {args...};
        prod = cml::numeric::product<args...>();
    }
};

template<size_t... T>
B<size_t> test3(){
    auto v = vector<size_t>{{T...}};
    cout << v << endl;
    cout << &v[0] << endl;
    return B<size_t>(std::move(v));
}

template<size_t... dims>
void test4_helper(cml::nd_array<int, sizeof...(dims)> a){
    auto arr = cml::MultiDimensionalInitializerListProcessor<int, dims...>::getArray(a);
    print(cout, arr.begin(), arr.end());
}

void test4(){
    test4_helper<3, 2, 2>({
        {
            {1, 2},
            {3, 4}
        },
        {
            {5},
            {7, 8}
        },
        {
            {90, 10},
            {11, 12}
        }
    });
}


int main(){
    test1();
    // test2<4>({1, 2, 3, 4});
    // test2<2, 2>({{1, 2}, {3, 4}});

//     auto b = test3<1, 2, 3>();
//     cout << b.v << endl;
//     cout << &b.v[0] << endl;
//     b.set<4, 5, 6, 7, 8>();
//     cout << b.v << endl;
//     cout << &b.v[0] << endl;
//     cout << b.prod << endl;
    
    test4();
}
