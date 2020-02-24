
#include "array_attributes.h"
#include "dtypes.h"
#include "utils.h"

using namespace std;
using namespace numeric;

array_attributes::array_attributes(Dtype dtype): dtype{dtype} {}

array_attributes::array_attributes(const vector<size_t>& shape, Dtype dtype):
    shape{shape},
    size{size_t(sum(shape))},
    dtype{dtype},
    dtypesize{DtypeSizes[int(dtype)]},
    data{malloc(dtypesize * size), free} {}

// array_attributes::array_attributes(initializer_list<size_t> shape, Dtype dtype):
//     shape{shape},
//     size{size_t(sum(shape))},
//     dtype{dtype},
//     dtypesize{DtypeSizes[int(dtype)]} {}
