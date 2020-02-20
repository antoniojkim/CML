#pragma once

#include <complex>
#include <cstdint>

namespace numeric {

    #define ALL_TYPES(PREFIX, SELECT, SUFFIX)                   \
        PREFIX SELECT(std::int8_t, int8) SUFFIX                 \
        PREFIX SELECT(std::int16_t, int16) SUFFIX               \
        PREFIX SELECT(std::int32_t, int32) SUFFIX               \
        PREFIX SELECT(std::int64_t, int64) SUFFIX               \
        PREFIX SELECT(std::uint8_t, uint8) SUFFIX               \
        PREFIX SELECT(std::uint16_t, uint16) SUFFIX             \
        PREFIX SELECT(std::uint32_t, uint32) SUFFIX             \
        PREFIX SELECT(std::uint64_t, uint64) SUFFIX             \
        PREFIX SELECT(float, float32) SUFFIX                    \
        PREFIX SELECT(double, float64) SUFFIX                   \
        PREFIX SELECT(long double, float80) SUFFIX              \
        PREFIX SELECT(std::complex<float>, cfloat32) SUFFIX     \
        PREFIX SELECT(std::complex<double>, cfloat64) SUFFIX

    #define NUM_DTYPES 13

    enum class Dtype: std::int8_t {
        Undefined,

        #define PREFIX
        #define SELECT(_1, _2)  _2
        #define SUFFIX ,

        ALL_TYPES(PREFIX, SELECT, SUFFIX)

        #undef PREFIX
        #undef SELECT
        #undef SUFFIX

        size  // Number of Dtypes
    };

    constexpr std::size_t DtypeSizes[NUM_DTYPES + 2] = {
        0,

        #define PREFIX 
        #define SELECT(_1, _2)  sizeof ( _1 )
        #define SUFFIX ,

        ALL_TYPES(PREFIX, SELECT, SUFFIX)

        #undef PREFIX
        #undef SELECT
        #undef SUFFIX

        0
    };

}
