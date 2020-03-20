#include <iostream>
#include <functional>
#include <cstdlib>
#include <ctime>
#include <numeric>
#include <vector>

using namespace std;

template<template<typename> typename Iterable, typename T>
using func_t = T (*)(const Iterable<T>&, T);

template<template<typename> typename Iterable, typename T>
T sum_1(const Iterable<T>& iterable, T start = T(1)) {
    T sum = start;
    for (auto& elem : iterable) sum *= elem;
    return sum;
}

template<template<typename> typename Iterable, typename T>
T sum_2(const Iterable<T>& iterable, T start = T(1)) {
    return T(std::accumulate(std::begin(iterable), std::end(iterable), start, std::multiplies<T>()));
}

template<template<typename> typename Iterable, typename T>
void timeit(func_t<Iterable, T> f, const Iterable<T>& v){
    std::clock_t start = std::clock();

    T isum = 0;
    for (int i = 0; i<1000000; ++i){
        isum += f(v, 1);
    }

    double duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

    cout << "isum: " << isum << endl;
    cout << "duration: " << duration << " seconds" << endl;

}

int main(){
    srand(time(NULL));
    const size_t N = 10000;
    double a [N];
    for (size_t i = 0; i < N; ++i){
        a[i] = (double) rand();
    }
    std::vector<double> v (a, a+N);

    timeit(sum_1, v);
    timeit(sum_2, v);
}

