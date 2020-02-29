
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

// template<typename T>
// void copy_2il(initializer_list<initializer_list<T>> il, T* data){
//     size_t index = 0;
//     for(auto l : il){
//         std::copy(std::begin(l), std::end(l), data+index);
//         index += l.size();
//     }
// }

// template<typename T>
// Array::Array(initializer_list<initializer_list<T>> l, Dtype dtype):
//     a{make_unique<array_attributes>(vector<size_t>{l.size(), l.begin().size()}, dtype)} {

//     switch(dtype){
//         #define SELECT(AT, DT) case Dtype::DT: copy_2il(l, (AT*) a->data.get()); break;
        
//         ARRAY_TYPES(PREFIX, SELECT, SUFFIX)
        
//         #undef SELECT

//         default:  throw numeric::Exception("Invalid Type Error");
//     }
// }

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
