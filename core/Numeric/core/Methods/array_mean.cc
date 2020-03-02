
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
T Array<T>::mean() const {
    if (a.size == 0){
        throw numeric::Exception("Cannot compute mean of empty array.");
    }
    return numeric::sum(a.data.get(), a.size) / (T) a.size;
}

template<typename T>
void Array<T>::mean(T& out) const {
    if (a.size == 0){
        throw numeric::Exception("Cannot compute mean of empty array.");
    }
    out = numeric::sum(a.data.get(), a.size) / a.size;
}


#define PREFIX
#define SELECT(T, _2)                           \
    template T Array<T>::mean() const;         \
    template void Array<T>::mean(T&) const;
#define SUFFIX

ARRAY_TYPES(PREFIX, SELECT, SUFFIX)
COMPLEX_TYPES(PREFIX, SELECT, SUFFIX)

#undef PREFIX
#undef SELECT
#undef SUFFIX
