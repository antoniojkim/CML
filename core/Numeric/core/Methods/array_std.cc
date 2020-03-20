
#include <cassert>
#include <cmath>

#include "../array.h"
#include "../array_attributes.h"
#include "../dtypes.h"
#include "../exception.h"
#include "../utils.h"

using namespace std;
using namespace numeric;

#define PREFIX
#define SUFFIX

template<typename T>
T Array<T>::std(long ddof) const {
    if (a.size == 0){
        throw numeric::Exception("Cannot compute std of empty array.");
    }
    return numeric::std(a.data.get(), a.size, ddof);
}

template<typename T>
void Array<T>::std(T& out, long ddof) const {
    if (a.size == 0){
        throw numeric::Exception("Cannot compute std of empty array.");
    }
    out = numeric::std(a.data.get(), a.size, ddof);
}


#define PREFIX
#define SELECT(T, _2)                               \
    template T Array<T>::std(long) const;           \
    template void Array<T>::std(T&, long) const;
#define SUFFIX

ARRAY_TYPES(PREFIX, SELECT, SUFFIX)
COMPLEX_TYPES(PREFIX, SELECT, SUFFIX)

#undef PREFIX
#undef SELECT
#undef SUFFIX
