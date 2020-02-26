#include <iostream>

#include <Catch2>

using namespace std;

#include <Numeric/array.h>
#include <Numeric/dtypes.h>

using namespace numeric;

TEST_CASE("Array `all` tests", "[all]"){

    SECTION("`Empty Array Test"){
        Array a (Dtype::int32);
        REQUIRE( a.dtype() == Dtype::int32 );
        REQUIRE( a.size() == 0 );
        REQUIRE( a.ndim() == 1 );
        REQUIRE( a.all() );
    }

    SECTION("`all` Test (true)"){
        Array a ({1, 1, 1, 1}, Dtype::int32);
        REQUIRE( a.dtype() == Dtype::int32 );
        REQUIRE( a.size() == 4 );
        REQUIRE( a.all() );
    }

    SECTION("`all` Test (false)"){
        Array a ({0, 1, 0, 1}, Dtype::int32);
        REQUIRE( a.dtype() == Dtype::int32 );
        REQUIRE( a.size() == 4 );
        REQUIRE( a.ndim() == 1 );
        REQUIRE( !a.all() );
    }

    SECTION("`all` Test (true, non zero values)"){
        Array a ({1, -1, 2, -4, 5}, Dtype::int32);
        REQUIRE( a.dtype() == Dtype::int32 );
        REQUIRE( a.size() == 5 );
        REQUIRE( a.ndim() == 1 );
        REQUIRE( a.all() );
    }

    SECTION("`all` Test (false, non zero values)"){
        Array a ({1, -1, 2, -4, 0}, Dtype::int32);
        REQUIRE( a.dtype() == Dtype::int32 );
        REQUIRE( a.size() == 5 );
        REQUIRE( a.ndim() == 1 );
        REQUIRE( !a.all() );
    }

    SECTION("`all` Test (true, floats)"){
        Array a ({1.0, -1.0, 2.0, -4.0, 5.0});
        REQUIRE( a.dtype() == Dtype::float32 );
        REQUIRE( a.size() == 5 );
        REQUIRE( a.ndim() == 1 );
        REQUIRE( a.all() );
    }

    SECTION("`all` Test (false, floats)"){
        Array a ({1.0, -1.0, 2.0, -4.0, 0.0});
        REQUIRE( a.dtype() == Dtype::float32 );
        REQUIRE( a.size() == 5 );
        REQUIRE( a.ndim() == 1 );
        REQUIRE( !a.all() );
    }

}

