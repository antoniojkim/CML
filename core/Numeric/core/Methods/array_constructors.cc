
#include <algorithm>
#include <numeric>
#include <vector>
#include <iostream>

#include "../array.h"
#include "../array_attributes.h"
#include "../dtypes.h"
#include "../exception.h"
#include "../utils.h"

using namespace std;
using namespace numeric;

#include <cstdlib>

template<typename T>
numeric::Array<T> numeric::array(){ return Array<T>(); }
template<typename T>
numeric::Array<T> numeric::array(const std::vector<std::size_t>& shape){ return Array<T>(shape); }
template<typename T>
numeric::Array<T> numeric::array(std::initializer_list<T> l){
    Array<T> a (vector<size_t>{l.size()});

    std::copy(std::begin(l), std::end(l), (T*) a.data().get());

    return a;
}


#define PREFIX
#define SUFFIX

#define SELECT(T, _2) template numeric::Array<T> numeric::array<T>();

ARRAY_TYPES(PREFIX, SELECT, SUFFIX)
COMPLEX_TYPES(PREFIX, SELECT, SUFFIX)

#undef SELECT

#define SELECT(T, _2) template numeric::Array<T> numeric::array<T>(const std::vector<size_t>&);

ARRAY_TYPES(PREFIX, SELECT, SUFFIX)
COMPLEX_TYPES(PREFIX, SELECT, SUFFIX)

#undef SELECT

#define SELECT(T, _2) template numeric::Array<T> numeric::array<T>(std::initializer_list<T>);

ARRAY_TYPES(PREFIX, SELECT, SUFFIX)
COMPLEX_TYPES(PREFIX, SELECT, SUFFIX)

#undef SELECT

#undef PREFIX
#undef SUFFIX
