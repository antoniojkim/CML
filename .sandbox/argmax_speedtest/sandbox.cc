
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

typedef size_t (*func_t)(float*, int);

size_t distance_max_iterator(float* A, int N){
    return distance(A, max_element(A, A + N));
}

size_t argmax_loop(float* A, int N){
    size_t index = 0;
    for(int i = 1; i < N; ++i){
        if (A[i] > A[index]){
            index = i;
        }
    }
    return index;
}

size_t argmax_loop_2(float* A, int N){
    float* max = A;
    float* end = A+N;
    for(float* a = A+1; a != end; ++a){
        if (*a > *max){
            max = a;
        }
    }
    return (size_t)(max - A);
}

void timeit(func_t f, float* a, int N){
    std::clock_t start = std::clock();

    size_t isum = 0;
    for (int i = 0; i<100000; ++i){
        isum += f(a, N);
    }

    double duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

    cout << "isum: " << isum << endl;
    cout << "duration: " << duration << " seconds" << endl;

}

int main(){
    srand(time(NULL));
    const int N = 10000;
    float a[N];
    for (int i = 0; i < N; ++i){
        a[i] = (float) rand();
    }

    timeit(distance_max_iterator, a, N);
    timeit(argmax_loop, a, N);
    timeit(argmax_loop_2, a, N);
}
