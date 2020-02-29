#include <iostream>

#include <Catch2>

using namespace std;

#include <Numeric/array.h>
#include <Numeric/dtypes.h>

using namespace numeric;

TEST_CASE("Basic Array Construction Tests", "[basic]"){

    using numeric::array;

    SECTION("Empty Array Test"){
        Array a;
        REQUIRE( a.dtype() == Dtype::float32 );
    }

    SECTION("Simple 1D Array Test"){
        auto a = array<float>({1, 2, 3, 4});
        REQUIRE( a.dtype() == Dtype::float32 );
        REQUIRE( a.itemsize() == sizeof(float) );
        REQUIRE( a.shape() == vector<size_t>{4} );
        REQUIRE( a.size() == 4 );
        REQUIRE( a.ndim() == 1 );
    }

    SECTION("Simple 1D Array Test (different type)"){
        auto a = array<int>({1, 2});
        REQUIRE( a.dtype() == Dtype::int32 );
        REQUIRE( a.itemsize() == sizeof(int) );
        REQUIRE( a.shape() == vector<size_t>{2} );
        REQUIRE( a.size() == 2 );
        REQUIRE( a.ndim() == 1 );
    }

}

