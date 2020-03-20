#include <iostream>
#include <functional>
#include <cstdlib>
#include <ctime>
#include <numeric>
#include <vector>

using namespace std;

template<typename T>
using func_t = T (*)(const T*, const std::size_t, T);

template<typename T>
T sum_1(const T* array, const std::size_t size, T start = T(0)) {
    T sum = start;
    for (size_t i = 0; i < size; ++i) sum += array[i];
    return sum;
}

template<typename T>
T sum_2(const T* array, const std::size_t size, T start = T(0)) {
    return T(std::accumulate(array, array+size, T(0), std::plus<T>()));
}

template<typename T>
T sum_3(const T* array, const std::size_t size, T start = T(0)) {
    const T* elem = array;
    const T* end = array+size;
    T sum = start;
    while (elem != end) sum += *(elem++);
    return sum;
}

template<typename T>
void timeit(func_t<T> f, const T* a,const size_t N){
    std::clock_t start = std::clock();

    T isum = 0;
    for (int i = 0; i<1000000; ++i){
        isum += f(a, N, 0);
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

    timeit(sum_1, a, N);
    timeit(sum_2, a, N);
    timeit(sum_3, a, N);
}

