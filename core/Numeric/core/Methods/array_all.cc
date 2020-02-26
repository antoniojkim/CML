
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
bool Array<T>::all(){
    if (ndim() != 1){
        throw numeric::Exception("Array::all without axis requires array to be 1D. Got: ", ndim());
    }

    return numeric::all((T*) a->data.get(), a->size);
}

template<typename T>
inline void Array<T>::all(bool& out){
    out = all();
}
