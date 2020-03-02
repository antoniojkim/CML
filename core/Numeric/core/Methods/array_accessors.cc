
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
T& Array<T>::get(long index) const {
#ifndef NO_ERROR_CHECKING
    if (index >= (int) a->size || index < -((int) a->size)){
        throw numeric::Exception("Array index out of bounds: ", index,
                                 "  Expected: [", -a->size, ", ", a->size, ")");
    }
#endif

    if (index >= 0){
        return a->data.get()[index];
    }
    return a->data.get()[a->size + index];
}

template<typename T>
T& Array<T>::get(const std::vector<long>& indices) const {
#ifndef NO_ERROR_CHECKING
    if (indices.size() != ndim()){
        throw numeric::Exception("Array::get received an incorrect number of indices. ",
                                 " Expected: ", ndim(), ".  Got: ", indices.size() );
    }
#endif

    long axis;
    long index = 0;
    for (size_t i = 0; i < indices.size(); ++i){
        axis = (long) shape()[i];

#ifndef NO_ERROR_CHECKING
        if (indices[i] >= axis || indices[i] < -axis){
            throw numeric::Exception("Array index out of bounds at axis ", i, ". ",
                                    " Expected: [", -axis, ", ", axis, ").  Got: ", indices[i]);
        }
#endif

        if (indices[i] >= 0){
            index = index * axis + indices[i];
        }
        else{
            index = (index + 1) * axis + indices[i];
        }
    }

    return a->data.get()[index];
}


#define PREFIX
#define SUFFIX

#define SELECT(T, _2) template T& Array<T>::get(long) const;

ARRAY_TYPES(PREFIX, SELECT, SUFFIX)
COMPLEX_TYPES(PREFIX, SELECT, SUFFIX)

#undef SELECT

#define SELECT(T, _2) template T& Array<T>::get(const std::vector<long>&) const;

ARRAY_TYPES(PREFIX, SELECT, SUFFIX)
COMPLEX_TYPES(PREFIX, SELECT, SUFFIX)

#undef SELECT

#undef PREFIX
#undef SUFFIX
