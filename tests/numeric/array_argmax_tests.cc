#include <iostream>

#include <Catch2>

using namespace std;

#include <Numeric/array.h>
#include <Numeric/dtypes.h>

using namespace numeric;

TEST_CASE("Array `argmax` tests", "[argmax]"){

    SECTION("`Empty Array Test"){
        Array<int> a;
        REQUIRE( a.dtype() == Dtype::int32 );
        REQUIRE( a.size() == 0 );
        REQUIRE( a.ndim() == 1 );
        REQUIRE( a.argmax() == 0 );
    }

    SECTION("`argmax` Test (all equal)"){
        Array<int> a ({1, 1, 1, 1});
        REQUIRE( a.dtype() == Dtype::int32 );
        REQUIRE( a.size() == 4 );
        REQUIRE( a.argmax() == 0 );
    }

    SECTION("`argmax` Test (some equal)"){
        Array<int> a ({0, 1, 0, 1});
        REQUIRE( a.dtype() == Dtype::int32 );
        REQUIRE( a.size() == 4 );
        REQUIRE( a.ndim() == 1 );
        REQUIRE( a.argmax() == 1 );
    }

    SECTION("`argmax` Test (some negatives)"){
        Array<int> a ({1, -1, 2, -4, 5});
        REQUIRE( a.dtype() == Dtype::int32 );
        REQUIRE( a.size() == 5 );
        REQUIRE( a.ndim() == 1 );
        REQUIRE( a.argmax() == 4 );
    }

    SECTION("`argmax` Test (some negatives and zero)"){
        Array<int> a ({1, -1, 2, -4, 0});
        REQUIRE( a.dtype() == Dtype::int32 );
        REQUIRE( a.size() == 5 );
        REQUIRE( a.ndim() == 1 );
        REQUIRE( a.argmax() == 2 );
    }

    SECTION("`argmax` Test (positive, negative floats)"){
        Array a ({1.0, -1.0, 2.0, -4.0, 5.0});
        REQUIRE( a.dtype() == Dtype::float32 );
        REQUIRE( a.size() == 5 );
        REQUIRE( a.ndim() == 1 );
        REQUIRE( a.argmax() == 4 );
    }

    SECTION("`argmax` Test (floats with zero)"){
        Array a ({1.0, -1.0, 2.0, -4.0, 0.0});
        REQUIRE( a.dtype() == Dtype::float32 );
        REQUIRE( a.size() == 5 );
        REQUIRE( a.ndim() == 1 );
        REQUIRE( a.argmax() == 2 );
    }

}

