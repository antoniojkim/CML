
#include <iostream>

using namespace std;

#define ARRAY_TYPES(PREFIX, SELECT, SUFFIX)                 \
    PREFIX SELECT(std::int8_t, int8) SUFFIX                 \
    PREFIX SELECT(short int, int16) SUFFIX                  \
    PREFIX SELECT(int, int32) SUFFIX                        \
    PREFIX SELECT(long long, int64) SUFFIX                  \
    PREFIX SELECT(std::uint8_t, uint8) SUFFIX               \
    PREFIX SELECT(unsigned short int, uint16) SUFFIX        \
    PREFIX SELECT(unsigned int, uint32) SUFFIX              \
    PREFIX SELECT(unsigned long long, uint64) SUFFIX        \
    PREFIX SELECT(float, float32) SUFFIX                    \
    PREFIX SELECT(double, float64) SUFFIX

#define PREFIX1 template Array<T>::Array
#define SELECT1(U, _2) (std::initializer_list<U>)
#define SUFFIX1 ;

#define EXPAND(X) X


#define PREFIX
#define SELECT(T, _2) EXPAND(ARRAY_TYPES(PREFIX1, SELECT1, SUFFIX1))
#define SUFFIX

ARRAY_TYPES(PREFIX, SELECT, SUFFIX)

#undef EXPAND
#undef PREFIX
#undef SELECT
#undef SUFFIX
#undef PREFIX1
#undef SELECT1
#undef SUFFIX1

int main(){

}
