
#include <numeric>
#include <vector>
#include <utility>

#include "array.h"
#include "array_attributes.h"
#include "dtypes.h"
#include "utils.h"

using namespace std;
using namespace numeric;

template<typename T>
Array<T>::Array(): a{make_unique<array_attributes<T>>()} {
    a->shape.reserve(4);
}

template<typename T>
Array<T>::Array(const std::vector<size_t>& v):
    a{make_unique<array_attributes<T>>(v)} {}

template<typename T>
Array<T>::Array(const Array<T>& other):
    a{make_unique<array_attributes<T>>(*other.a)}{}

template<typename T>
Array<T>::Array(Array<T>&& other):
    a{std::move(other.a)}{}

template<typename T>
Array<T>::~Array() = default;

template<typename T>
ArrayIter<T> Array<T>::begin(){
    throw "Unimplemented Error";
}
template<typename T>
ArrayIter<T> Array<T>::end(){
    throw "Unimplemented Error";
}

template<typename T> 
shared_ptr<T[]> Array<T>::data(){ return a->data; }
template<typename T>
Dtype Array<T>::dtype(){ return array_attributes<T>::dtype; }
template<typename T>
size_t Array<T>::itemsize(){ return array_attributes<T>::dtypesize; }
template<typename T>
uint64_t Array<T>::nbytes(){
    return ((uint64_t) a->dtype) * ((uint64_t) a->dtypesize);
}

template<typename T>
const vector<std::size_t>& Array<T>::shape(){ return a->shape; }
template<typename T>
size_t Array<T>::size(){ return a->size; }
template<typename T>
size_t Array<T>::ndim(){ return a->shape.size(); }

template<typename T>
Array<T> array(){
    return Array<T>();
}


namespace std {
    template<typename T>
    numeric::ArrayIter<T> begin(numeric::Array<T>& a){
        return a.begin();
    }
    template<typename T>
    numeric::ArrayIter<T> end(numeric::Array<T>& a){
        return a.end();
    }
}


#define PREFIX
#define SELECT(T, _2) template class Array<T>;
#define SUFFIX

ARRAY_TYPES(PREFIX, SELECT, SUFFIX)
COMPLEX_TYPES(PREFIX, SELECT, SUFFIX)

#undef PREFIX
#undef SELECT
#undef SUFFIX
