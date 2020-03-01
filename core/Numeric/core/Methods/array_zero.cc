
#include <cassert>

#include "../array.h"
#include "../array_attributes.h"
#include "../dtypes.h"
#include "../exception.h"
#include "../utils.h"

using namespace std;
using namespace numeric;

template<typename T>
Array<T> Array<T>::zero() const {
    Array<T> out;
    *out.a = this->a->zero();

    if (out.size() != this->size()){
        throw numeric::Exception("Array::zero produces different size results: ", this->size(), " != ", out.size());
    }

    return out;
}


#define PREFIX
#define SELECT(T, _2) template Array<T> Array<T>::zero() const;
#define SUFFIX

ARRAY_TYPES(PREFIX, SELECT, SUFFIX)
COMPLEX_TYPES(PREFIX, SELECT, SUFFIX)

#undef PREFIX
#undef SELECT
#undef SUFFIX
