
#include "array_attributes.h"
#include "dtypes.h"
#include "utils.h"

using namespace std;
using namespace numeric;

template<typename T>
array_attributes<T>::array_attributes() {}

template<typename T>
array_attributes<T>::array_attributes(const vector<size_t>& shape):
    shape{shape},
    size{size_t(sum(shape))},
    data{new T[size]} {}


#define PREFIX
#define SELECT(T, _2) template class array_attributes<T>;
#define SUFFIX

ARRAY_TYPES(PREFIX, SELECT, SUFFIX)

#undef PREFIX
#undef SELECT
#undef SUFFIX
