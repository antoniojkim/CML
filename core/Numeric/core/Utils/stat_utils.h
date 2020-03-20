#pragma once

#include <cmath>

#include "accumulators.h"

namespace numeric {

    template<typename T>
    inline T mean(const T* array, const std::size_t size) {
        return T(sum(array, size) / (T) size);
    }

    template<template<typename> typename Iterable, typename T>
    inline T mean(const Iterable<T>& iterable){
        return T(sum(iterable) / (T) iterable.size());
    }

    template<typename T>
    T var(const T* array, const std::size_t size, long ddof = 0) {
        double sum = (double) numeric::sum(array, size);
        double mean = sum / (double) size;

        double sq_sum = 0;
        double diff;
        for (size_t i = 0; i < size; ++i){
            diff = double(array[i]) - mean;
            sq_sum += diff * diff;
        }

        return T(sq_sum / ((double) size - ddof));
    }

    template<template<typename> typename Iterable, typename T>
    T var(const Iterable<T>& iterable, long ddof = 0){
        double sum = (double) numeric::sum(iterable);
        double mean = sum / (T) iterable.size();

        double sq_sum = 0;
        double diff;
        for (auto& elem : iterable){
            diff = elem - mean;
            sq_sum += diff * diff;
        }

        return T(sq_sum / ((double) iterable.size() - ddof));
    }

    template<typename T>
    inline T std(const T* array, const std::size_t size, long ddof = 0) {
        return T(std::sqrt(var(array, size, ddof)));
    }

    template<template<typename> typename Iterable, typename T>
    inline T std(const Iterable<T>& iterable, long ddof = 0){
        return T(std::sqrt(var(iterable, ddof)));
    }
}
