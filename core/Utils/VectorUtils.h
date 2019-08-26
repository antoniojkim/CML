#ifndef __CML__UTILS_VECTORUTILS_H__
#define __CML__UTILS_VECTORUTILS_H__

#include <vector>
#include <ostream>

template <typename Iterator>
std::ostream& print(std::ostream& out, Iterator begin, Iterator end ) {
    out << "[";
    if (begin != end){ out << *(begin++); }
    while (begin != end) { out << ", " << *(begin++); }
    out << "]";
    return out;
}

template<typename T>
inline std::ostream& operator<<(std::ostream& out, std::vector<T>& v){ return print(out, v.begin(), v.end()); }
template<typename T>
inline std::ostream& operator<<(std::ostream& out, std::initializer_list<T> v){ return print(out, v.begin(), v.end()); }

namespace cml {

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
