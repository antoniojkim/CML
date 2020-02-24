
#include <algorithm>
#include <numeric>
#include <vector>

#include "../array.h"
#include "../array_attributes.h"
#include "../dtypes.h"
#include "../exception.h"
#include "../utils.h"

using namespace std;
using namespace numeric;

#define PREFIX
#define SUFFIX

#include <cstdlib>

template<typename T>
Array::Array(std::initializer_list<T> l, Dtype dtype):
    a{make_unique<array_attributes>(vector<size_t>{l.size()}, dtype)} {

    switch(dtype){
        #define SELECT(AT, DT) case Dtype::DT: std::copy(std::begin(l), std::end(l), (AT*) a->data.get()); break;
        
        ARRAY_TYPES(PREFIX, SELECT, SUFFIX)
        
        #undef SELECT

        default:  throw numeric::Exception("Invalid Type Error");
    }
}
    
#define INSTANTIATE_ARRAY_VECTOR_DTYPE(T, _2) \
    template Array::Array(std::initializer_list<T> l, Dtype dtype);

ARRAY_TYPES(PREFIX, INSTANTIATE_ARRAY_VECTOR_DTYPE, SUFFIX)

#undef INSTANTIATE_ARRAY_VECTOR_DTYPE


#undef PREFIX
#undef SUFFIX
