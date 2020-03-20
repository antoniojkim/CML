
#include <numeric>
#include <functional>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <vector>

using namespace std;

template<template<typename> typename Iterable, typename T>
using func_t = T (*)(const Iterable<T>&, long);

template<template<typename> typename Iterable, typename T>
T std_1(const Iterable<T>& iterable, long ddof = 0){
    double sum = (double) std::accumulate(std::begin(iterable), std::end(iterable), T(0), std::plus<T>());
    double mean = sum / (T) iterable.size();

    std::vector<double> diff(iterable.size());
    std::transform(std::begin(iterable), std::end(iterable), diff.begin(),
                    [mean](double x) { return x - mean; });
    double sq_sum = std::inner_product(diff.begin(), diff.end(), diff.begin(), 0.0);
    double stdev = std::sqrt(sq_sum / double(diff.size() - ddof));

    return T(stdev);
}

template<template<typename> typename Iterable, typename T>
T std_2(const Iterable<T>& iterable, long ddof = 0){
    double sum = (double) std::accumulate(std::begin(iterable), std::end(iterable), T(0), std::plus<T>());
    double mean = sum / (T) iterable.size();

    double sq_sum = 0;
    double diff;
    for (auto& elem : iterable){
        diff = elem - mean;
        sq_sum += diff * diff;
    }
    double stdev = std::sqrt(sq_sum / ((double) iterable.size() - ddof));

    return T(stdev);
}

template<template<typename> typename Iterable, typename T>
void timeit(func_t<Iterable, T> f, const Iterable<T>& iterable){
    std::clock_t start = std::clock();

    T isum = 0;
    for (int i = 0; i<100000; ++i){
        isum += f(iterable, 1);
    }

    double duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

    cout << "isum: " << isum << endl;
    cout << "duration: " << duration << " seconds" << endl;

}

int main(){
    srand(time(NULL));
    const size_t N = 10000;
    std::vector<float> v (N);
    for (size_t i = 0; i < N; ++i){
        v.emplace_back((float) rand());
    }

    timeit(std_1<vector, float>, v);
    timeit(std_2<vector, float>, v);
}

