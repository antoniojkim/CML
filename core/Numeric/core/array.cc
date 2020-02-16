
#include <numeric>

#include "../array.h"

using namespace std;
using namespace numeric;

struct array_attributes {
    std::vector<int> shape;
    uint64_t size;
    Dtype dtype;
    DtypeSize dtypesize

    // Data
    std::shared_ptr<void *> data = nullptr;

    array_attributes(Dtype dtype): dtype{dtype} {}
    array_attributes(const std::vector<int>& shape, Dtype dtype):
        shape{shape},
        size{std::accumulate(std::begin(shape),
                             std::end(shape), 1, std::multiplies<double>())}, 
        dtype{dtype} {}
};


Array::Array(Dtype dtype): a{make_unique<array_attributes>(dtype)} {
    a->shape.reserve(4);
}

const std::vector<int>& Array::shape(){ return a->shape; }
const std::vector<int>& Array::size(){ return a->size; }
