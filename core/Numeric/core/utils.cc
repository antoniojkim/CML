
#include <numeric>

#include "dtypes.h"
#include "../utils.h"

using namespace std;
using namespace numeric;
#define PREFIX
#define SUFFIX

/*******************************************************************************
 *********************************** sum ***************************************
 *******************************************************************************/

template<template<typename> typename Iterable, typename T>
T sum(const Iterable<T>& iter) {
    return T(std::accumulate(std::begin(v), std::end(v), T(0), std::plus<T>()));
}

#define INSTANTIATE_SUM(T, _2) \
    template T sum<std::vector, T>(const std::vector<T>& v);

ALL_TYPES(PREFIX, INSTANTIATE_SUM, SUFFIX)

#define INSTANTIATE_SUM(T, _2) \
    template T sum<std::initializer_list, T>(const std::initializer_list<T>& v);

ALL_TYPES(PREFIX, INSTANTIATE_SUM, SUFFIX)

#undef INSTANTIATE_SUM


/*******************************************************************************
 ********************************* product *************************************
 *******************************************************************************/

template<template<typename> typename Iterable, typename T>
T product(const Iterable<T>& iter) {
    return T(std::accumulate(std::begin(v), std::end(v), T(1), std::multiplies<T>()));
}

#define INSTANTIATE_PRODUCT(T, _2) \
    template T product<std::vector, T>(const std::vector<T>& v);

ALL_TYPES(PREFIX, INSTANTIATE_PRODUCT, SUFFIX)

#define INSTANTIATE_PRODUCT(T, _2) \
    template T product<std::initializer_list, T>(const std::initializer_list<T>& v);

ALL_TYPES(PREFIX, INSTANTIATE_PRODUCT, SUFFIX)

#undef INSTANTIATE_PRODUCT
