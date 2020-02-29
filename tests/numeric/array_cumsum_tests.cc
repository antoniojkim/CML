#include <iostream>

#include <Catch2>

using namespace std;

#include <Numeric/array.h>
#include <Numeric/dtypes.h>

using namespace numeric;

TEST_CASE("Array `cumsum` tests", "[cumsum]"){

    using numeric::array;

    SECTION("`Empty Array Test"){
        Array<int> a;
        REQUIRE( a.dtype() == Dtype::int32 );
        REQUIRE( a.size() == 0 );
        REQUIRE( a.ndim() == 1 );
        REQUIRE( a.cumsum() == array<int>() );
    }

    SECTION("`cumsum` Test (int)"){
        auto a = array<int>({1, 2, 3});
        REQUIRE( a.dtype() == Dtype::int32 );
        REQUIRE( a.size() == 3 );
        REQUIRE( a.cumsum() == array<int>({1, 3, 6}) );
    }

    SECTION("`cumsum` Test 2 (int)"){
        auto a = array<int>({1, 2, 3, 4, 5, 6});
        REQUIRE( a.dtype() == Dtype::int32 );
        REQUIRE( a.size() == 6 );
        REQUIRE( a.cumsum() == array<int>({1, 3, 6, 10, 15, 21}) );
    }

    SECTION("`cumsum` Test (some negatives)"){
        auto a = array<int>({1, -1, 2, -4, 5});
        REQUIRE( a.dtype() == Dtype::int32 );
        REQUIRE( a.size() == 5 );
        REQUIRE( a.cumsum() == array<int>({1, 0, 2, -2, 3}) );
    }

    SECTION("`cumsum` Test (some negatives and zero)"){
        auto a = array<int>({1, -1, 2, -4, 0});
        REQUIRE( a.dtype() == Dtype::int32 );
        REQUIRE( a.size() == 5 );
        REQUIRE( a.cumsum() == array<int>({1, 0, 2, -2, -2}) );
    }

    SECTION("`cumsum` Test (positive, negative floats)"){
        auto a = array<float>({1.0, -1.0, 2.0, -4.0, 5.0});
        REQUIRE( a.dtype() == Dtype::float32 );
        REQUIRE( a.size() == 5 );
        REQUIRE( a.ndim() == 1 );
        REQUIRE( a.cumsum() == array<float>({1, 0, 2, -2, 3}) );
    }

    SECTION("`cumsum` Test (floats with zero)"){
        auto a = array({1.0, -1.0, 2.0, -4.0, 0.0});
        REQUIRE( a.dtype() == Dtype::float64 );
        REQUIRE( a.size() == 5 );
        REQUIRE( a.ndim() == 1 );
        REQUIRE( a.cumsum() == array<double>({1, 0, 2, -2, -2}) );
    }

}

