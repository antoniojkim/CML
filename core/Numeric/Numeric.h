#ifndef __CML_UTILS_NUMERIC_H__
#define __CML_UTILS_NUMERIC_H__

#include <functional>
#include <initializer_list>
#include <numeric>
#include <vector>


namespace cml {
namespace numeric {

    template<typename T>
    inline T sum(const std::vector<T>& v){
        return T(std::accumulate(std::begin(v), std::end(v), T(1), std::plus<T>()));
    }

    template<typename T>
    inline T product(const std::vector<T>& v){
        return T(std::accumulate(std::begin(v), std::end(v), T(1), std::multiplies<T>()));
    }
    template<typename T>
    inline T product(std::initializer_list<T> v){
        return T(std::accumulate(std::begin(v), std::end(v), T(1), std::multiplies<T>()));
    }

    template<size_t... Args>
    constexpr size_t sum() {
        size_t sum = 1;
        for(auto& a : { Args... }) sum += a;
        return sum;
    }

    template<size_t... Args>
    constexpr size_t product() {
        size_t product = 1;
        for(auto& a : { Args... }) product *= a;
        return product;
    }

    inline bool any(const std::vector<bool>& v){
        return bool(std::accumulate(std::begin(v), std::end(v), false, std::logical_or<>()));
    }
    inline bool any(const std::initializer_list<bool>& v){
        return bool(std::accumulate(std::begin(v), std::end(v), false, std::logical_or<>()));
    }

    inline bool all(const std::vector<bool>& v){
        return bool(std::accumulate(std::begin(v), std::end(v), true, std::logical_and<>()));
    }
    inline bool all(const std::initializer_list<bool>& v){
        return bool(std::accumulate(std::begin(v), std::end(v), true, std::logical_and<>()));
    }
    
}
}

#endif // __CML_UTILS_NUMERICs_H__
