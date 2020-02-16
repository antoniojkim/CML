#pragma once

#include <complex>
#include <cstdint>

namespace numeric {

    #define ALL_TYPES(PREFIX, SELECT, SUFFIX) \
        PREFIX SELECT(bool, boolean) SUFFIX \
        PREFIX SELECT(int8_t, int8) SUFFIX \
        PREFIX SELECT(int16_t, int16) SUFFIX \
        PREFIX SELECT(int32_t, int32) SUFFIX \
        PREFIX SELECT(int64_t, int64) SUFFIX \
        PREFIX SELECT(uint8_t, uint8) SUFFIX \
        PREFIX SELECT(uint16_t, uint16) SUFFIX \
        PREFIX SELECT(uint32_t, uint32) SUFFIX \
        PREFIX SELECT(uint64_t, uint64) SUFFIX \
        PREFIX SELECT(float, float32) SUFFIX \
        PREFIX SELECT(double, float64) SUFFIX \
        PREFIX SELECT(long double, float80) SUFFIX \
        PREFIX SELECT(std::complex<float>, cfloat32) SUFFIX \
        PREFIX SELECT(std::complex<double>, cfloat64) SUFFIX \

    enum class Dtype: int8_t {
        #define PREFIX
        #define SELECT(_1, _2)  _2
        #define SUFFIX ,

        ALL_TYPES(PREFIX, SELECT, SUFFIX)

        #undef PREFIX
        #undef SELECT
        #undef SUFFIX

        size,  // Number of Dtypes
        Undefined
    };

    enum class DtypeSizes: int8_t {
        #define PREFIX
        #define SELECT(_1, _2) sizeof(_1)
        #define SUFFIX ,

        ALL_TYPES(PREFIX, SELECT, SUFFIX)

        #undef PREFIX
        #undef SELECT
        #undef SUFFIX
        
        size  // Number of Dtypes
    };

}
