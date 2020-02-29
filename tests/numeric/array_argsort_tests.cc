#include <iostream>

#include <Catch2>

using namespace std;

#include <Numeric/array.h>
#include <Numeric/dtypes.h>

using namespace numeric;

TEST_CASE("Array `argsort` tests", "[argsort]"){

    using numeric::array;

    SECTION("`Empty Array Test"){
        Array<int> a;
        REQUIRE( a.dtype() == Dtype::int32 );
        REQUIRE( a.size() == 0 );
        REQUIRE( a.ndim() == 1 );
        REQUIRE( a.argsort() == vector<size_t>{} );
    }

    SECTION("`argsort` Test (all equal)"){
        auto a = array<int>({1, 1, 1, 1});
        REQUIRE( a.dtype() == Dtype::int32 );
        REQUIRE( a.size() == 4 );
        REQUIRE( a.argsort() == vector<size_t>{0, 1, 2, 3} );
    }

    SECTION("`argsort` Test (some equal)"){
        auto a = array<int>({0, 1, 0, 1});
        REQUIRE( a.dtype() == Dtype::int32 );
        REQUIRE( a.size() == 4 );
        REQUIRE( a.ndim() == 1 );
        REQUIRE( a.argsort() == vector<size_t>{0, 2, 1, 3} );
    }

    SECTION("`argsort` Test (some negatives)"){
        auto a = array<int>({1, -1, 2, -4, 5});
        REQUIRE( a.dtype() == Dtype::int32 );
        REQUIRE( a.size() == 5 );
        REQUIRE( a.ndim() == 1 );
        REQUIRE( a.argsort() == vector<size_t>{3, 1, 0, 2, 4} );
    }

    SECTION("`argsort` Test (some negatives and zero)"){
        auto a = array<int>({1, -1, 2, -4, 0});
        REQUIRE( a.dtype() == Dtype::int32 );
        REQUIRE( a.size() == 5 );
        REQUIRE( a.ndim() == 1 );
        REQUIRE( a.argsort() == vector<size_t>{3, 1, 4, 0, 2} );
    }

    SECTION("`argsort` Test (positive, negative floats)"){
        auto a = array<float>({1.0, -1.0, 2.0, -4.0, 5.0});
        REQUIRE( a.dtype() == Dtype::float32 );
        REQUIRE( a.size() == 5 );
        REQUIRE( a.ndim() == 1 );
        REQUIRE( a.argsort() == vector<size_t>{3, 1, 0, 2, 4} );
    }

    SECTION("`argsort` Test (floats with zero)"){
        auto a = array({1.0, -1.0, 2.0, -4.0, 0.0});
        REQUIRE( a.dtype() == Dtype::float64 );
        REQUIRE( a.size() == 5 );
        REQUIRE( a.ndim() == 1 );
        REQUIRE( a.argsort() == vector<size_t>{3, 1, 4, 0, 2} );
    }

}

