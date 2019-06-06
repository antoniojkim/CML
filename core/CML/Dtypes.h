#ifndef __CML_DTYPES_H__
#define __CML_DTYPES_H__

#include <type_traits>

namespace cml {
    
    #define INSTANTIATE_CLASS_TEMPLATES(T) \
        template class T<float>; \
        template class T<double>; \
        template class T<long long>; \
        template class T<long>; \
        template class T<int>;

    /*
        The following 6 declarations come from:
            http://coliru.stacked-crooked.com/a/a9b7a1e17e580291

        They are used to prevent perfect argument forwarding from 
        taking effect in certain contexts
    */

    template <typename T>
    using RemoveReference = typename std::remove_reference<T>::type;

    template <typename T>
    using RemoveCv = typename std::remove_cv<T>::type;

    template <bool T, typename U = void>
    using DisableIf = typename std::enable_if<!T, U>::type;

    template <typename T>
    using Bare = RemoveCv<RemoveReference<T>>;

    template <typename T, typename... U>
    struct is_related : std::false_type {};

    template <typename T, typename U>
    struct is_related<T, U> : std::is_same<Bare<T>, Bare<U>> {};

    namespace nn {
            
        enum Reduction {
            NONE,
            SUM,
            MEAN
        };

    }
    
}

#endif // __CML_DTYPES_H__
