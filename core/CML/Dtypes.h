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

}

#endif // __CML_DTYPES_H__
