#pragma once

#include <functional>
#include <cstdlib>
#include <numeric>
#include <iostream>

namespace numeric {

    template<typename T>
    size_t argmax(T* array, std::size_t size){
        T* max = array;
        T* end = array+size;
        for(T* a = array+1; a < end; ++a){
            if (*a > *max){
                max = a;
            }
        }
        return (size_t)(max - array);
    }

    template<typename T>
    size_t argmin(T* array, std::size_t size){
        T* min = array;
        T* end = array+size;
        for(T* a = array+1; a < end; ++a){
            if (*a < *min){
                min = a;
            }
        }
        return (size_t)(min - array);
    }

    template<typename T>
    std::vector<size_t> argsort(T* a, std::size_t N){
        std::vector<size_t> idx(N);
        std::iota(idx.begin(), idx.end(), 0);
        std::sort(idx.begin(), idx.end(), [a](const size_t &i, const size_t &j){ return a[i] < a[j];});
        return idx;
    }

}