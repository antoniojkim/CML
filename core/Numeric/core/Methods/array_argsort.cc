
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
vector<size_t> Array<T>::argsort() const {
    return numeric::argsort(a.data.get(), a.size);
}


#define PREFIX
#define SELECT(T, _2) template vector<size_t> Array<T>::argsort() const;
#define SUFFIX

ARRAY_TYPES(PREFIX, SELECT, SUFFIX)
COMPLEX_TYPES(PREFIX, SELECT, SUFFIX)

#undef PREFIX
#undef SELECT
#undef SUFFIX
