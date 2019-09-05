#ifndef __CML_DTYPES_H__
#define __CML_DTYPES_H__

#include <initializer_list>
#include <map>
#include <string>
#include <type_traits>

namespace cml {

    #define INSTANTIATE_CLASS_TEMPLATES(T) \
        template class T<float>; \
        template class T<double>; \
        template class T<long long>; \
        template class T<long>; \
        template class T<int>;

    #define INSTANTIATE_FUNCTION_TEMPLATES(T) \
        template float T<float>(const float&); \
        template double T<double>(const double&); \
        template long long T<long long>(const long long&); \
        template long T<long>(const long&); \
        template int T<int>(const int&);


    namespace nn {

        enum Reduction {
            NONE,
            SUM,
            MEAN
        };

    }

//     typedef std::initializer_list<std::pair<std::string, double>> Kwargs;
    typedef std::map<std::string, double> Kwargs;


    // This definition of the conjunction class comes from
    // https://www.fluentcpp.com/2019/01/25/variadic-number-function-parameters-type/
    template<bool...> struct bool_pack{};
    template<class... Ts>
    using conjunction = std::is_same<bool_pack<true,Ts::value...>, bool_pack<Ts::value..., true>>;

    template<typename... T>
    using AllIntegral =
        typename std::enable_if<cml::conjunction<std::is_integral<T>...>::value>::type;

    // std::is_convertible<T, std::string>::value
}

#endif // __CML_DTYPES_H__
