
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <numeric>
#include <functional>

using namespace std;

template<typename T>
bool all(const T* array, const std::size_t& size, T start = T(true)){
    auto out = std::accumulate(array, array+size, start, std::logical_and<T>());
    cout << "out == " << out << " == ";
    return bool(out);
}

int main(){
    if (1.0f){
        cout << "1.0f implicit convert to true" << endl;
    }
    else {
        cout << "1.0f implicit convert to false" << endl;
    }

    if (1.0f && -2.0f){
        cout << "1.0f && -2.0f implicit convert to true" << endl;
    }
    else {
        cout << "1.0f && -2.0f implicit convert to false" << endl;
    }

    shared_ptr<void> p(malloc(sizeof(float) * 5), free);
    float arr[5] = {1.0, -1.0, 2.0, -4.0, 5.0};
    std::copy(arr, arr+5, (float*) p.get());
    
    cout << "float(true) == " << float(true) << endl;
    cout << "all == " << all(arr, 5, float(true)) << endl;
    cout << "all == " << all((float*) p.get(), 5) << endl;

    float result = true;
    cout << "result";
    for (int i = 0; i < 5; ++i){
        result = result && arr[i];
        cout << " == " << result;
    }
    cout << endl;
}
