#pragma once

#include <complex>
#include <cstdint>
#include <cstdlib>
#include <type_traits>

#include "exception.h"

namespace numeric {

    #define ARRAY_TYPES(PREFIX, SELECT, SUFFIX)            \
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

    #define COMPLEX_TYPES(PREFIX, SELECT, SUFFIX)               \
        PREFIX SELECT(std::complex<float>, cfloat32) SUFFIX     \
        PREFIX SELECT(std::complex<double>, cfloat64) SUFFIX


    #define NUM_DTYPES 13

    enum class Dtype: std::int8_t {
        Undefined,

        #define PREFIX
        #define SELECT(_1, _2)  _2
        #define SUFFIX ,

        ARRAY_TYPES(PREFIX, SELECT, SUFFIX)
        COMPLEX_TYPES(PREFIX, SELECT, SUFFIX)

        #undef PREFIX
        #undef SELECT
        #undef SUFFIX

        size  // Number of Dtypes
    };

    template<typename T>
    constexpr Dtype TYPE_TO_DTYPE(){

        #define PREFIX 
        #define SELECT(AT, DT)  if(std::is_same<T, AT>::value){ return Dtype::DT; }
        #define SUFFIX

        ARRAY_TYPES(PREFIX, SELECT, SUFFIX)

        #undef PREFIX
        #undef SELECT
        #undef SUFFIX

        return Dtype::Undefined;
    }

    // template<typename T>
    // Dtype type_to_dtype();

    // #define PREFIX 
    // #define SELECT(T, DT) template<> Dtype type_to_dtype<T>(){ return Dtype::DT; }
    // #define SUFFIX

    // ARRAY_TYPES(PREFIX, SELECT, SUFFIX)

    // #undef PREFIX 
    // #undef SELECT
    // #undef SUFFIX

}
