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

    SECTION("Zero Array Test"){
        Array<int> a (vector<size_t>{5, 2});
        REQUIRE( a.dtype() == Dtype::int32 );
        REQUIRE( a.size() == 10 );
        REQUIRE( a.ndim() == 2 );

        Array<int> b = a.zero();
        REQUIRE( b.dtype() == Dtype::int32 );
        REQUIRE( b.size() == 10 );
        REQUIRE( b.ndim() == 2 );
        for (size_t i = 0; i < b.size(); ++i){
            REQUIRE( b[i] == 0 );
        }

        b.fill(3);
        for (size_t i = 0; i < b.size(); ++i){
            REQUIRE( b[i] == 3 );
        }
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

