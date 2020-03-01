
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
shared_ptr<T[]> Array<T>::data() const { return a->data; }
template<typename T>
Dtype Array<T>::dtype() const { return array_attributes<T>::dtype; }
template<typename T>
size_t Array<T>::itemsize() const { return array_attributes<T>::dtypesize; }
template<typename T>
uint64_t Array<T>::nbytes() const {
    return ((uint64_t) a->dtype) * ((uint64_t) a->dtypesize);
}

template<typename T>
const vector<std::size_t>& Array<T>::shape() const { return a->shape; }
template<typename T>
std::size_t Array<T>::rows() const { return a->shape[0]; }
template<typename T>
std::size_t Array<T>::cols() const { return a->shape[1]; }
template<typename T>
size_t Array<T>::size() const { return a->size; }
template<typename T>
size_t Array<T>::ndim() const { return a->shape.size(); }


template<typename T>
bool operator==(const Array<T>& a1, const Array<T>& a2){

    if (a1.size() != a2.size() || a1.ndim() != a2.ndim() || a1.shape() != a2.shape()){
        return false;
    }

    T* d1 = (T*) a1.data().get();
    T* d2 = (T*) a2.data().get();

    for(size_t i = 0; i < a1.size(); ++i){
        if (d1[i] != d2[i]){
            return false;
        }
    }

    return true;
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
#define SUFFIX

#define SELECT(T, _2) template class Array<T>;

ARRAY_TYPES(PREFIX, SELECT, SUFFIX)
COMPLEX_TYPES(PREFIX, SELECT, SUFFIX)

#undef SELECT

#define SELECT(T, _2) template bool operator==<T>(const Array<T>&, const Array<T>&);

ARRAY_TYPES(PREFIX, SELECT, SUFFIX)
COMPLEX_TYPES(PREFIX, SELECT, SUFFIX)

#undef SELECT

#undef PREFIX
#undef SUFFIX
