
#include <cassert>

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
bool Array<T>::any() const {
    if (ndim() != 1){
        throw numeric::Exception("Array::all without axis requires array to be 1D. Got: ", ndim());
    }

    return numeric::any((T*) a->data.get(), a->size);
}

template<typename T>
inline void Array<T>::any(bool& out) const {
    out = any();
}


#define PREFIX
#define SELECT(T, _2)                       \
    template bool Array<T>::any() const;    \
    template void Array<T>::any(bool&) const;
#define SUFFIX

ARRAY_TYPES(PREFIX, SELECT, SUFFIX)
COMPLEX_TYPES(PREFIX, SELECT, SUFFIX)

#undef PREFIX
#undef SELECT
#undef SUFFIX
