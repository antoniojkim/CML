
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

// array_attributes::array_attributes(initializer_list<size_t> shape, Dtype dtype):
//     shape{shape},
//     size{size_t(sum(shape))},
//     dtype{dtype},
//     dtypesize{DtypeSizes[int(dtype)]} {}
