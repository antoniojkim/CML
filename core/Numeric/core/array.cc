
#include <numeric>
#include <vector>

#include "array.h"
#include "array_attributes.h"
#include "dtypes.h"
#include "utils.h"

using namespace std;
using namespace numeric;

Array::Array(Dtype dtype): a{make_unique<array_attributes>(dtype)} {
    a->shape.reserve(4);
}
Array::Array(const std::vector<size_t>& v, Dtype dtype):
    a{make_unique<array_attributes>(v, dtype)} {}
Array::~Array() = default;

ArrayIter Array::begin(){
    throw "Unimplemented Error";
}
ArrayIter Array::end(){
    throw "Unimplemented Error";
}

shared_ptr<void> Array::data(){ return a->data; }
Dtype Array::dtype(){ return a->dtype; }
size_t Array::itemsize(){ return a->dtypesize; }
uint64_t Array::nbytes(){
    return ((uint64_t) a->dtype) * ((uint64_t) a->dtypesize);
}

const vector<std::size_t>& Array::shape(){ return a->shape; }
size_t Array::size(){ return a->size; }
size_t Array::ndim(){ return a->shape.size(); }

Array array(Dtype dtype){
    return Array(dtype);
}


namespace std {
    template <> numeric::ArrayIter begin(numeric::Array& a){
        return a.begin();
    }
    template <> numeric::ArrayIter end(numeric::Array& a){
        return a.end();
    }
}
