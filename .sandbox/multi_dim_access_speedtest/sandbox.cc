#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

constexpr long shape[3] = {20, 20, 30};

typedef float (*func_t)(float*, long);

float& get(float* a, long N, const vector<long>& indices){
    long index = 0;
    for (size_t i = 0; i < indices.size(); ++i){

        if (indices[i] >= shape[i]){
            cout << indices[i] << "    " << shape[i] << endl;
            throw "ERROR";
        }

        index = index * shape[i] + indices[i];
    }
    return a[index];
}

float access_all_elements(float* a, long N){
    float sum = 0;
    for (long i = 0; i < shape[0]; ++i){
        for (long j = 0; j < shape[1]; ++j){
            for (long k = 0; k < shape[2]; ++k){
                sum += get(a, N, {i, j, k});
            }
        }
    }
    return sum;
}


void timeit(func_t f, float* a, int N){
    std::clock_t start = std::clock();

    float isum = 0;
    for (int i = 0; i<10000; ++i){
        isum += f(a, N);
    }

    double duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

    cout << "isum: " << isum << endl;
    cout << "duration: " << duration << " seconds" << endl;

}

int main(){
    srand(time(NULL));
    constexpr long N = shape[0] * shape[1] * shape[2];
    float a[N];
    for (long i = 0; i < N; ++i){
        a[i] = (float) rand();
    }

    timeit(access_all_elements, a, N);
}

