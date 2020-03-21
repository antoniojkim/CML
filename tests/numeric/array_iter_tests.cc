#include <iostream>

#include <Catch2>

using namespace std;

#include <Numeric/array.h>
#include <Numeric/dtypes.h>
#include <Numeric/utils.h>

using namespace numeric;

TEST_CASE("Array `iter` tests", "[mean]"){

    using numeric::array;

    SECTION("`iter` Test (all equal)"){
        auto a = array<int>({1, 1, 1, 1});
        REQUIRE( a.dtype() == Dtype::int32 );
        REQUIRE( a.size() == 4 );
        REQUIRE( mean(a) == 1 );
    }

    SECTION("`iter` Test (some equal)"){
        auto a = array<int>({0, 1, 0, 1});
        REQUIRE( a.dtype() == Dtype::int32 );
        REQUIRE( a.size() == 4 );
        REQUIRE( a.ndim() == 1 );
        REQUIRE( mean(a) == 0 );
    }

    SECTION("`iter` Test (some negatives)"){
        auto a = array<int>({1, -1, 7, -4, 5});
        REQUIRE( a.dtype() == Dtype::int32 );
        REQUIRE( a.size() == 5 );
        REQUIRE( a.ndim() == 1 );
        REQUIRE( mean(a) == 1 );
    }

    SECTION("`iter` Test (some negatives and zero)"){
        auto a = array<int>({1, -3, 2, -5, 0});
        REQUIRE( a.dtype() == Dtype::int32 );
        REQUIRE( a.size() == 5 );
        REQUIRE( a.ndim() == 1 );
        REQUIRE( mean(a) == -1 );
    }

    SECTION("`iter` Test (positive, negative floats)"){
        auto a = array<float>({1.0, -1.0, 2.0, -4.0, 5.0});
        REQUIRE( a.dtype() == Dtype::float32 );
        REQUIRE( a.size() == 5 );
        REQUIRE( a.ndim() == 1 );
        REQUIRE( mean(a) == 0.6f );
    }

    SECTION("`iter` Test (floats with zero)"){
        auto a = array({1.0, -1.0, 2.0, -4.0, 0.0});
        REQUIRE( a.dtype() == Dtype::float64 );
        REQUIRE( a.size() == 5 );
        REQUIRE( a.ndim() == 1 );
        REQUIRE( mean(a) == -0.4 );
    }

}

