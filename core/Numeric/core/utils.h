#pragma once

#include <functional>
#include <cstdlib>
#include <numeric>
#include <iostream>

namespace numeric {

    template<typename T>
    T sum(const T* array, const std::size_t& size, T start = 0) {
        return T(std::accumulate(array, array+size, start, std::plus<T>()));
    }

    template<template<typename> typename Iterable, typename T>
    T sum(const Iterable<T>& iterable, T start = 0){
        return T(std::accumulate(std::begin(iterable), std::end(iterable), start, std::plus<T>()));
    }


    template<typename T>
    T product(const T* array, const std::size_t& size, T start = 1){
        return T(std::accumulate(array, array+size, start, std::multiplies<T>()));
    }

    template<template<typename> typename Iterable, typename T>
    T product(const Iterable<T>& iterable, T start = 1){
        return T(std::accumulate(std::begin(iterable), std::end(iterable), start, std::multiplies<T>()));
    }


    template<typename T>
    bool all(const T* array, const std::size_t& size, T start = (T) true){
        return bool(std::accumulate(array, array+size, start, std::logical_and<T>()));
    }

    template<template<typename> typename Iterable, typename T>
    bool all(const Iterable<T>& iterable, T start = (T) true){
        return bool(std::accumulate(std::begin(iterable), std::end(iterable), start, std::logical_and<T>()));
    }


    template<typename T>
    bool any(const T* array, const std::size_t& size, T start = false){
        return bool(std::accumulate(array, array+size, start, std::logical_or<T>()));
    }

    template<template<typename> typename Iterable, typename T>
    bool any(const Iterable<T>& iterable, T start = false){
        return bool(std::accumulate(std::begin(iterable), std::end(iterable), start, std::logical_or<T>()));
    }


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

}
