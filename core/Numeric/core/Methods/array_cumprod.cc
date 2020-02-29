
#include <cassert>

#include "../array.h"
#include "../array_attributes.h"
#include "../dtypes.h"
#include "../exception.h"
#include "../utils.h"

using namespace std;
using namespace numeric;

#define PREFIX
#define SUFFIX

template<typename T>
Array<T> Array<T>::cumprod() const {
    Array<T> out = this->zero();
    cumprod(out);
    return out;
}

template<typename T>
void Array<T>::cumprod(Array<T>& out) const {
    if (out.size() != this->size()){
        throw numeric::Exception("Array::cumprod expected an array of size ", this->size(), ". Got: ", out.size());
    }

    T* out_data = (T*) out.data().get();
    T* data = (T*) this->data().get();
    
    if (out.size() > 0){
        out_data[0] = data[0];
        for (size_t i = 1; i < out.size(); ++i){
            out_data[i] = data[i] * out_data[i-1];
        }
    }
}


#define PREFIX
#define SELECT(T, _2)                                    \
    template Array<T> Array<T>::cumprod() const;         \
    template void Array<T>::cumprod(Array<T>&) const;
#define SUFFIX

ARRAY_TYPES(PREFIX, SELECT, SUFFIX)
COMPLEX_TYPES(PREFIX, SELECT, SUFFIX)

#undef PREFIX
#undef SELECT
#undef SUFFIX
