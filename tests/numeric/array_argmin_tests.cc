#include <iostream>

#include <Catch2>

using namespace std;

#include <Numeric/array.h>
#include <Numeric/dtypes.h>

using namespace numeric;

TEST_CASE("Array `argmin` tests", "[argmin]"){

    using numeric::array;

    SECTION("`Empty Array Test"){
        Array<int> a;
        REQUIRE( a.dtype() == Dtype::int32 );
        REQUIRE( a.size() == 0 );
        REQUIRE( a.ndim() == 1 );
        REQUIRE( a.argmin() == 0 );
    }

    SECTION("`argmin` Test (all equal)"){
        auto a = array<int>({1, 1, 1, 1});
        REQUIRE( a.dtype() == Dtype::int32 );
        REQUIRE( a.size() == 4 );
        REQUIRE( a.argmin() == 0 );
    }

    SECTION("`argmin` Test (some equal)"){
        auto a = array<int>({0, 1, 0, 1});
        REQUIRE( a.dtype() == Dtype::int32 );
        REQUIRE( a.size() == 4 );
        REQUIRE( a.ndim() == 1 );
        REQUIRE( a.argmin() == 0 );
    }

    SECTION("`argmin` Test (some negatives)"){
        auto a = array<int>({1, -1, 2, -4, 5});
        REQUIRE( a.dtype() == Dtype::int32 );
        REQUIRE( a.size() == 5 );
        REQUIRE( a.ndim() == 1 );
        REQUIRE( a.argmin() == 3 );
    }

    SECTION("`argmin` Test (some negatives and zero)"){
        auto a = array<int>({1, -1, 2, -4, 0});
        REQUIRE( a.dtype() == Dtype::int32 );
        REQUIRE( a.size() == 5 );
        REQUIRE( a.ndim() == 1 );
        REQUIRE( a.argmin() == 3 );
    }

    SECTION("`argmin` Test (positive, negative floats)"){
        auto a = array<float>({1.0, -1.0, 2.0, -4.0, 5.0});
        REQUIRE( a.dtype() == Dtype::float32 );
        REQUIRE( a.size() == 5 );
        REQUIRE( a.ndim() == 1 );
        REQUIRE( a.argmin() == 3 );
    }

    SECTION("`argmin` Test (floats with zero)"){
        auto a = array({1.0, -1.0, 2.0, -4.0, 0.0});
        REQUIRE( a.dtype() == Dtype::float64 );
        REQUIRE( a.size() == 5 );
        REQUIRE( a.ndim() == 1 );
        REQUIRE( a.argmin() == 3 );
    }

}

