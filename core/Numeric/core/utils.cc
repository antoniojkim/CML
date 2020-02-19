
#include <functional>
#include <initializer_list>
#include <numeric>
#include <vector>

#include "dtypes.h"
#include "utils.h"

using namespace std;
using namespace numeric;
#define PREFIX
#define SUFFIX

/*******************************************************************************
 *********************************** sum ***************************************
 *******************************************************************************/

template<template<typename> typename Iterable, typename T>
T sum(const Iterable<T>& iter) {
    return T(std::accumulate(std::begin(iter), std::end(iter), T(0), std::plus<T>()));
}

#define INSTANTIATE_SUM(T, _2) \
    template<> T sum(const std::vector<T>& v);

ALL_TYPES(PREFIX, INSTANTIATE_SUM, SUFFIX)

#define INSTANTIATE_SUM(T, _2) \
    template<> T sum(const std::initializer_list<T>& l);

ALL_TYPES(PREFIX, INSTANTIATE_SUM, SUFFIX)

#undef INSTANTIATE_SUM


/*******************************************************************************
 ********************************* product *************************************
 *******************************************************************************/

template<template<typename> typename Iterable, typename T>
T product(const Iterable<T>& iter) {
    return T(std::accumulate(std::begin(iter), std::end(iter), T(1), std::multiplies<T>()));
}

#define INSTANTIATE_PRODUCT(T, _2) \
    template<> T product(const std::vector<T>& v);

ALL_TYPES(PREFIX, INSTANTIATE_PRODUCT, SUFFIX)

#define INSTANTIATE_PRODUCT(T, _2) \
    template<> T product(const std::initializer_list<T>& l);

ALL_TYPES(PREFIX, INSTANTIATE_PRODUCT, SUFFIX)

#undef INSTANTIATE_PRODUCT
