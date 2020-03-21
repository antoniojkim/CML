
#include <algorithm>
#include <numeric>
#include <vector>
#include <utility>

#include "array.h"
#include "array_attributes.h"
#include "dtypes.h"
#include "printer.h"
#include "utils.h"

using namespace std;
using namespace numeric;

template<typename T>
Array<T>::Array() {
    a.shape.reserve(4);
}

template<typename T>
Array<T>::Array(const std::vector<size_t>& v): a{v} {}

template<typename T>
Array<T>::Array(const Array<T>& other): a{other.a}{}

template<typename T>
Array<T>::Array(Array<T>&& other): a{std::move(other.a)}{}

template<typename T>
Array<T>::~Array() = default;

template<typename T>
Array<T>::ArrayIter::ArrayIter(const Array<T>* array, int index): array{array}, index{index} {}
template<typename T>
void Array<T>::ArrayIter::operator++() { ++index; }
template<typename T>
bool Array<T>::ArrayIter::operator!=(const ArrayIter& other) const {
    return array != other.array || index != other.index;
}
template<typename T>
T Array<T>::ArrayIter::operator*() const { return (*array)[index]; }

template<typename T>
typename Array<T>::ArrayIter Array<T>::begin() const {
    return typename Array<T>::ArrayIter(this, 0);
}
template<typename T>
typename Array<T>::ArrayIter Array<T>::end() const {
    return typename Array<T>::ArrayIter(this, this->size());
}

template<typename T> 
shared_ptr<T[]> Array<T>::data() const { return a.data; }
template<typename T>
Dtype Array<T>::dtype() const { return array_attributes<T>::dtype; }
template<typename T>
size_t Array<T>::itemsize() const { return array_attributes<T>::dtypesize; }
template<typename T>
uint64_t Array<T>::nbytes() const {
    return ((uint64_t) a.dtype) * ((uint64_t) a.dtypesize);
}

template<typename T>
const vector<std::size_t>& Array<T>::shape() const { return a.shape; }
template<typename T>
std::size_t Array<T>::rows() const { return a.shape[0]; }
template<typename T>
std::size_t Array<T>::cols() const { return a.shape[1]; }
template<typename T>
size_t Array<T>::size() const { return a.size; }
template<typename T>
size_t Array<T>::ndim() const { return a.shape.size(); }


template<typename T>
void Array<T>::fill(T value){
    std::fill_n((T*) a.data.get(), a.size, value);
}


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

template<typename T = float>
std::ostream& operator<<(std::ostream& out, const numeric::Array<T>& array){
    return Printer::print(out, array);
}


namespace std {
    template<typename T>
    typename numeric::Array<T>::ArrayIter begin(const numeric::Array<T>& a){
        return a.begin();
    }
    template<typename T>
    typename numeric::Array<T>::ArrayIter end(const numeric::Array<T>& a){
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

#define SELECT(T, _2) template std::ostream& operator<<<T>(std::ostream&, const Array<T>&);

ARRAY_TYPES(PREFIX, SELECT, SUFFIX)
COMPLEX_TYPES(PREFIX, SELECT, SUFFIX)

#undef SELECT

#define SELECT(T, _2)                                                           \
    typename numeric::Array<T>::ArrayIter begin(const numeric::Array<T>& a);    \
    typename numeric::Array<T>::ArrayIter end(const numeric::Array<T>& a);

ARRAY_TYPES(PREFIX, SELECT, SUFFIX)
COMPLEX_TYPES(PREFIX, SELECT, SUFFIX)

#undef SELECT

#undef PREFIX
#undef SUFFIX
