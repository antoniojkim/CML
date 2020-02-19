
#include <numeric>
#include <vector>

#include "dtypes.h"
#include "array.h"

using namespace std;
using namespace numeric;

namespace numeric {
    struct array_attributes {
        vector<int> shape;
        uint64_t size;
        Dtype dtype;
        size_t dtypesize;

        // Data
        shared_ptr<void *> data = nullptr;

        array_attributes(Dtype dtype): dtype{dtype} {}
        array_attributes(const vector<int>& shape, Dtype dtype):
            shape{shape},
            size{uint64_t(std::accumulate(std::begin(shape),
                                        std::end(shape), 1, std::multiplies<double>()))},
            dtype{dtype},
            dtypesize{DtypeSizes[int(dtype)]} {}
    };
}


Array::Array(Dtype dtype): a{make_unique<array_attributes>(dtype)} {
    a->shape.reserve(4);
}

const vector<int>& Array::shape(){ return a->shape; }
uint64_t Array::size(){ return a->size; }


Array array(Dtype dtype){
    return Array(dtype);
}