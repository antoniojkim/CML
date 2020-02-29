
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
T& Array<T>::get(long index){
    if (index >= (int) a->size || index < -((int) a->size)){
        throw numeric::Exception("Array index out of bounds: ", index,
                                 "  Expected: [", -a->size, ", ", a->size, ")");
    }

    if (index >= 0){
        return a->data.get()[index];
    }
    return a->data.get()[a->size + index];
}


#define PREFIX
#define SELECT(T, _2) template T& Array<T>::get(long);
#define SUFFIX

ARRAY_TYPES(PREFIX, SELECT, SUFFIX)
COMPLEX_TYPES(PREFIX, SELECT, SUFFIX)

#undef PREFIX
#undef SELECT
#undef SUFFIX
