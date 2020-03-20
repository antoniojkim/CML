#pragma once

#include <functional>
#include <cstdlib>
#include <numeric>
#include <iostream>

namespace numeric {

    template<typename T>
    T sum(const T* array, const std::size_t size, T start = T(0)) {
        return T(std::accumulate(array, array+size, start, std::plus<T>()));
    }

    template<template<typename> typename Iterable, typename T>
    T sum(const Iterable<T>& iterable, T start = 0){
        return T(std::accumulate(std::begin(iterable), std::end(iterable), start, std::plus<T>()));
    }


    template<typename T>
    T product(const T* array, const std::size_t size, T start = 1){
        return T(std::accumulate(array, array+size, start, std::multiplies<T>()));
    }

    template<template<typename> typename Iterable, typename T>
    T product(const Iterable<T>& iterable, T start = 1){
        return T(std::accumulate(std::begin(iterable), std::end(iterable), start, std::multiplies<T>()));
    }


    template<typename T>
    bool all(const T* array, const std::size_t size){
        const T* end = array + size;
        for (const T* elem = array; elem != end; ++elem){
            if (!(*elem)) return false;
        }
        return true;
    }

    template<template<typename> typename Iterable, typename T>
    bool all(const Iterable<T>& iterable){
        for (auto& elem : iterable){
            if (!elem) return false;
        }
        return true;
    }


    template<typename T>
    bool any(const T* array, const std::size_t size){
        const T* end = array + size;
        for (const T* elem = array; elem != end; ++elem){
            if (*elem) return true;
        }
        return false;
    }

    template<template<typename> typename Iterable, typename T>
    bool any(const Iterable<T>& iterable){
        for (auto& elem : iterable){
            if (elem) return true;
        }
        return false;
    }

}