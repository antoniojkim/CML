
#include <algorithm>
#include <utility>

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
    size{size_t(product(shape))},
    data{new T[size]} {}

    
template<typename T>
array_attributes<T>::array_attributes(const array_attributes<T>& other):
    shape{other.shape},
    size{other.size},
    data{other.data} {}

    
template<typename T>
array_attributes<T>::array_attributes(array_attributes<T>&& other):
    shape{std::move(other.shape)},
    size{std::move(other.size)},
    data{std::move(other.data)} {}


template<typename T>
array_attributes<T> array_attributes<T>::copy() const{
    array_attributes<T> a {*this};
    a.data = shared_ptr<T[]>(new T[a.size]);
    std::copy((T*) this->data.get(), (T*) this->data.get() + this->size, (T*) a.data.get());
    return a;
}

template<typename T>
array_attributes<T> array_attributes<T>::zero() const{
    array_attributes<T> a {*this};
    a.data = shared_ptr<T[]>(new T[a.size]());
    return a;
}

template<typename T>
array_attributes<T>& array_attributes<T>::operator=(const array_attributes<T>& other){
    this->shape = other.shape;
    this->size = other.size;
    this->data = other.data;
    return *this;
}


#define PREFIX
#define SELECT(T, _2) template class array_attributes<T>;
#define SUFFIX

ARRAY_TYPES(PREFIX, SELECT, SUFFIX)
COMPLEX_TYPES(PREFIX, SELECT, SUFFIX)

#undef PREFIX
#undef SELECT
#undef SUFFIX
