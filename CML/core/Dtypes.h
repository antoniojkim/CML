#ifndef __CML_DTYPES_H__
#define __CML_DTYPES_H__

#include <initializer_list>
#include <map>
#include <string>
#include <type_traits>

namespace cml {

    #define WRAP_ALL_TYPES(PREFIX, SUFFIX) \
        PREFIX short int SUFFIX \
        PREFIX unsigned short int SUFFIX \
        PREFIX int SUFFIX \
        PREFIX unsigned int SUFFIX \
        PREFIX long int SUFFIX \
        PREFIX unsigned long int SUFFIX \
        PREFIX long long int SUFFIX \
        PREFIX unsigned long long int SUFFIX \
        PREFIX signed char SUFFIX \
        PREFIX unsigned char SUFFIX \
        PREFIX char SUFFIX \
        PREFIX float SUFFIX \
        PREFIX double SUFFIX \
        PREFIX long double SUFFIX \

    #define INSTANTIATE_CLASS_TEMPLATES(T) \
        WRAP_ALL_TYPES(template class T<, >;)\

    
    


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
