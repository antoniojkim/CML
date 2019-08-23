#ifndef __CML__UTILS_VECTORUTILS_H__
#define __CML__UTILS_VECTORUTILS_H__

#include <vector>
#include <ostream>

template <typename Iterator>
std::ostream& print(std::ostream& out, Iterator begin, Iterator end ) {
    out << "[";
    bool first = true;
    for (; begin != end; ++begin) {
        if (first){
            out << *begin;
            first = false;
        }
        else{
            out << ", " << *begin;
        }
    }
    out << "]";
    return out;
}
template<typename T>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T>& v){ return print(out, v.begin(), v.end()); }
template<typename T>
inline std::ostream& operator<<(std::ostream& out, std::initializer_list<T> v){ return print(out, v.begin(), v.end()); }

namespace cml {

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

    template<typename T, unsigned int N>
    struct NestedInitializerList {
        using type = std::initializer_list<typename NestedInitializerList<T, N - 1>::type>;
    };

    template<typename T>
    struct NestedInitializerList<T, 0> {
        using type = T;
    };
    
}







#endif // __CML__UTILS_VECTORUTILS_H__
