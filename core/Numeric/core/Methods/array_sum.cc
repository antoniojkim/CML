
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
T Array<T>::sum() const {
    if (a.size == 0){
        return 0;
    }
    return numeric::sum(a.data.get(), a.size);
}

template<typename T>
void Array<T>::sum(T& out) const {
    if (a.size == 0){
        out = 0;
    }
    else {
        out = numeric::sum(a.data.get(), a.size);
    }
}


#define PREFIX
#define SELECT(T, _2)                           \
    template T Array<T>::sum() const;         \
    template void Array<T>::sum(T&) const;
#define SUFFIX

ARRAY_TYPES(PREFIX, SELECT, SUFFIX)
COMPLEX_TYPES(PREFIX, SELECT, SUFFIX)

#undef PREFIX
#undef SELECT
#undef SUFFIX
