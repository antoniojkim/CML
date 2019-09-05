#ifndef __CML_UTILS_VECTORUTILS_H__
#define __CML_UTILS_VECTORUTILS_H__

#include <vector>
#include <ostream>

#include "../Numeric/Numeric.h"

class CMLException;

namespace cml {
    template <typename Iterator>
    std::ostream& print(std::ostream& out, Iterator begin, Iterator end){
        out << "[";
        if (begin != end){ out << *(begin++); }
        while (begin != end) { out << ", " << *(begin++); }
        out << "]";
        return out;
    }
    template<typename T>
    inline std::ostream& print(std::ostream& out, const std::vector<T>& v){
        return cml::print(out, v.begin(), v.end());
    }
    template<typename T>
    inline std::ostream& print(std::ostream& out, std::initializer_list<T> v){
        return cml::print(out, v.begin(), v.end());
    }
}

template<typename T>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T>& v){ return cml::print(out, v); }
template<typename T>
inline std::ostream& operator<<(std::ostream& out, std::initializer_list<T> v){ return cml::print(out, v); }
template<typename T, int N>
inline std::ostream& operator<<(std::ostream& out, std::array<T, N> a){ return cml::print(out, a.begin(), a.end()); }

// template std::ostream& operator<<<size_t>(std::ostream& out, const std::vector<size_t>& v);{ return cml::print(out, v.begin(), v.end()); }


namespace cml {

    template<typename T, unsigned int N>
    struct MultiDimensionalInitializerList {
        using type = std::initializer_list<typename MultiDimensionalInitializerList<T, N - 1>::type>;
    };

    template<typename T>
    struct MultiDimensionalInitializerList<T, 0> {
        using type = T;
    };

    template<typename T, unsigned int N>
    using nd_array = typename MultiDimensionalInitializerList<T, N>::type;

    template<typename T, size_t... dims>
    struct MultiDimensionalInitializerListProcessor;

    template<typename T, size_t first, size_t... rest>
    struct MultiDimensionalInitializerListProcessor<T, first, rest...> {

        static constexpr size_t R = cml::numeric::product<rest...>();
        static constexpr size_t S = first*R;
        static constexpr size_t N = 1+(sizeof...(rest));

        static std::array<T, S> getArray(nd_array<T, N> a){
            auto arr = std::array<T, S>();
            process(std::forward<nd_array<T, N>>(a), arr.data());
            return arr;
        }

        static void process(nd_array<T, N> a, T* data){
            if (a.size() > first){
                throw CMLException("Multidimensional Initializer list size is greater than first");
            }
            int i = 0;
            for (auto e : a){
                MultiDimensionalInitializerListProcessor<T, rest...>::process(e, data+R*(i++));
            }
        }

    };

    template<typename T, size_t last>
    struct MultiDimensionalInitializerListProcessor<T, last> {

        static void process(nd_array<T, 1> a, T* data){
            if (a.size() > last){
                throw CMLException("Multidimensional Initializer list size is greater than last");
            }
            for (auto e : a){
                *(data++) = e;
            }
        }

    };

}







#endif // __CML_UTILS_VECTORUTILS_H__
