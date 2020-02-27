
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <numeric>
#include <algorithm>
#include <vector>

using namespace std;

typedef std::vector<size_t> (*func_t)(float*, int);

std::vector<size_t> argsort_std(float* a, int N){
    std::vector<size_t> idx(N);
    std::iota(idx.begin(), idx.end(), 0);
    std::sort(idx.begin(), idx.end(), [a](const size_t &i, const size_t &j){ return a[i] < a[j];});
    return idx;
}

std::vector<size_t> argsort_stable(float* a, int N){
    std::vector<size_t> idx(N);
    std::iota(idx.begin(), idx.end(), 0);

    std::stable_sort(idx.begin(), idx.end(), [a](const size_t &i, const size_t &j)
                                               { return a[i] < a[j];});

    return idx;
}

void timeit(func_t f, float* a, int N){
    std::clock_t start = std::clock();

    const int iterations = 10000;
    for (int i = 0; i<iterations; ++i){
        auto r = f(a, N);
    }

    double duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

    cout << "duration: " << duration << " seconds" << endl;

}

int main(){
    srand(time(NULL));
    const int N = 10000;
    float a[N];
    for (int i = 0; i < N; ++i){
        a[i] = (float) rand();
    }

    timeit(argsort_std, a, N);
    timeit(argsort_stable, a, N);
}
