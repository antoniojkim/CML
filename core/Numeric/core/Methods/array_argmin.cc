
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
size_t Array<T>::argmin() const {
    return numeric::argmin(a.data.get(), a.size);
}

template<typename T>
void Array<T>::argmin(size_t& out) const {
    out = numeric::argmin(a.data.get(), a.size);;
}


#define PREFIX
#define SELECT(T, _2)                           \
    template size_t Array<T>::argmin() const;         \
    template void Array<T>::argmin(size_t&) const;
#define SUFFIX

ARRAY_TYPES(PREFIX, SELECT, SUFFIX)
COMPLEX_TYPES(PREFIX, SELECT, SUFFIX)

#undef PREFIX
#undef SELECT
#undef SUFFIX
