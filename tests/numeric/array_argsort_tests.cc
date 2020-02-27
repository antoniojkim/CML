#include <iostream>

#include <Catch2>

using namespace std;

#include <Numeric/array.h>
#include <Numeric/dtypes.h>

using namespace numeric;

TEST_CASE("Array `argsort` tests", "[argsort]"){

    SECTION("`Empty Array Test"){
        Array<int> a;
        REQUIRE( a.dtype() == Dtype::int32 );
        REQUIRE( a.size() == 0 );
        REQUIRE( a.ndim() == 1 );
        REQUIRE( a.argsort() == vector<size_t>{} );
    }

    SECTION("`argsort` Test (all equal)"){
        Array<int> a ({1, 1, 1, 1});
        REQUIRE( a.dtype() == Dtype::int32 );
        REQUIRE( a.size() == 4 );
        REQUIRE( a.argsort() == vector<size_t>{0, 1, 2, 3} );
    }

    SECTION("`argsort` Test (some equal)"){
        Array<int> a ({0, 1, 0, 1});
        REQUIRE( a.dtype() == Dtype::int32 );
        REQUIRE( a.size() == 4 );
        REQUIRE( a.ndim() == 1 );
        REQUIRE( a.argsort() == vector<size_t>{0, 2, 1, 3} );
    }

    SECTION("`argsort` Test (some negatives)"){
        Array<int> a ({1, -1, 2, -4, 5});
        REQUIRE( a.dtype() == Dtype::int32 );
        REQUIRE( a.size() == 5 );
        REQUIRE( a.ndim() == 1 );
        REQUIRE( a.argsort() == vector<size_t>{3, 1, 0, 2, 4} );
    }

    SECTION("`argsort` Test (some negatives and zero)"){
        Array<int> a ({1, -1, 2, -4, 0});
        REQUIRE( a.dtype() == Dtype::int32 );
        REQUIRE( a.size() == 5 );
        REQUIRE( a.ndim() == 1 );
        REQUIRE( a.argsort() == vector<size_t>{3, 1, 4, 0, 2} );
    }

    SECTION("`argsort` Test (positive, negative floats)"){
        Array a ({1.0, -1.0, 2.0, -4.0, 5.0});
        REQUIRE( a.dtype() == Dtype::float32 );
        REQUIRE( a.size() == 5 );
        REQUIRE( a.ndim() == 1 );
        REQUIRE( a.argsort() == vector<size_t>{3, 1, 0, 2, 4} );
    }

    SECTION("`argsort` Test (floats with zero)"){
        Array a ({1.0, -1.0, 2.0, -4.0, 0.0});
        REQUIRE( a.dtype() == Dtype::float32 );
        REQUIRE( a.size() == 5 );
        REQUIRE( a.ndim() == 1 );
        REQUIRE( a.argsort() == vector<size_t>{3, 1, 4, 0, 2} );
    }

}

