#ifndef __CML_DTYPES_H__
#define __CML_DTYPES_H__

namespace cml {
    
    #define INSTANTIATE_CLASS_TEMPLATES(T) \
        template class T<float>; \
        template class T<double>; \
        template class T<long long>; \
        template class T<long>; \
        template class T<int>;

    
}

#endif // __CML_DTYPES_H__
