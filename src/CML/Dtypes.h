#ifndef __CML_DTYPES_H__
#define __CML_DTYPES_H__

namespace cml {
    
    #define INSTANTIATE_TEMPLATES(T) \
        class template T<float>; \
        class template T<double>; \
        class template T<long long>; \
        class template T<long>; \
        class template T<int>;

    
}

#endif // __CML_DTYPES_H__
