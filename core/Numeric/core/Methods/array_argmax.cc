
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
size_t Array<T>::argmax() const {
    return numeric::argmax(a->data.get(), a->size);
}

template<typename T>
void Array<T>::argmax(size_t& out) const {
    out = numeric::argmax(a->data.get(), a->size);
}


#define PREFIX
#define SELECT(T, _2)                           \
    template size_t Array<T>::argmax() const;         \
    template void Array<T>::argmax(size_t&) const;
#define SUFFIX

ARRAY_TYPES(PREFIX, SELECT, SUFFIX)
COMPLEX_TYPES(PREFIX, SELECT, SUFFIX)

#undef PREFIX
#undef SELECT
#undef SUFFIX
