#pragma once

namespace numeric {

    template<template<typename> typename Iterable, typename T>
    T sum(const Iterable<T>& iterable);

    template<template<typename> typename Iterable, typename T>
    T product(const Iterable<T>& iterable);

}
