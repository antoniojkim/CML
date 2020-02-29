#include <iostream>

#include <Catch2>

using namespace std;

#include <Numeric/array.h>
#include <Numeric/dtypes.h>

using namespace numeric;

TEST_CASE("Array `cumprod` tests", "[cumprod]"){

    using numeric::array;

    SECTION("`Empty Array Test"){
        Array<int> a;
        REQUIRE( a.dtype() == Dtype::int32 );
        REQUIRE( a.size() == 0 );
        REQUIRE( a.ndim() == 1 );
        REQUIRE( a.cumprod() == array<int>() );
    }

    SECTION("`cumprod` Test (int)"){
        auto a = array<int>({1, 2, 3});
        REQUIRE( a.dtype() == Dtype::int32 );
        REQUIRE( a.size() == 3 );
        REQUIRE( a.cumprod() == array<int>({1, 2, 6}) );
    }

    SECTION("`cumprod` Test 2 (int)"){
        auto a = array<int>({1, 2, 3, 4, 5, 6});
        REQUIRE( a.dtype() == Dtype::int32 );
        REQUIRE( a.size() == 6 );
        REQUIRE( a.cumprod() == array<int>({1, 2, 6, 24, 120, 720}) );
    }

    SECTION("`cumprod` Test (some negatives)"){
        auto a = array<int>({1, -1, 2, -4, 5});
        REQUIRE( a.dtype() == Dtype::int32 );
        REQUIRE( a.size() == 5 );
        REQUIRE( a.cumprod() == array<int>({1, -1, -2, 8, 40}) );
    }

    SECTION("`cumprod` Test (some negatives and zero)"){
        auto a = array<int>({1, -1, 2, -4, 0});
        REQUIRE( a.dtype() == Dtype::int32 );
        REQUIRE( a.size() == 5 );
        REQUIRE( a.cumprod() == array<int>({1, -1, -2, 8, 0}) );
    }

    SECTION("`cumprod` Test (positive, negative floats)"){
        auto a = array<float>({1.0, -1.0, 2.0, -4.0, 5.0});
        REQUIRE( a.dtype() == Dtype::float32 );
        REQUIRE( a.size() == 5 );
        REQUIRE( a.ndim() == 1 );
        REQUIRE( a.cumprod() == array<float>({1, -1, -2, 8, 40}) );
    }

    SECTION("`cumprod` Test (floats with zero)"){
        auto a = array({1.0, -1.0, 2.0, -4.0, 0.0});
        REQUIRE( a.dtype() == Dtype::float64 );
        REQUIRE( a.size() == 5 );
        REQUIRE( a.ndim() == 1 );
        REQUIRE( a.cumprod() == array<double>({1, -1, -2, 8, 0}) );
    }

}

