
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

bool Array::all(){
    switch(a->dtype){
        #define PREFIX
        #define SELECT(T, DT) case Dtype::DT: return numeric::all((T*) a->data.get(), a->size);
        #define SUFFIX

        ARRAY_TYPES(PREFIX, SELECT, SUFFIX)
        
        #undef PREFIX
        #undef SELECT
        #undef SUFFIX

        default:  throw numeric::Exception("Invalid Type Error");
    }
}

inline void Array::all(bool& out){
    out = all();
}
