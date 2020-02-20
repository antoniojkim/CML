#include <iostream>

#include <Catch2>

using namespace std;

#include <Numeric/array.h>
#include <Numeric/dtypes.h>

using namespace numeric;

TEST_CASE("Basic Array Tests", "[basic]"){

    Array a;
    REQUIRE( a.dtype() == Dtype::float32 );

}

