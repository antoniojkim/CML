#include <iostream>

#include <Catch2>

using namespace std;

#include <Numeric/array.h>
#include <Numeric/dtypes.h>

using namespace numeric;

TEST_CASE("Array `copy` tests", "[copy]"){

    using numeric::array;

    SECTION("`copy` Test 1"){
        auto a = array<int>({1, 1, 1, 1});
        REQUIRE( a.dtype() == Dtype::int32 );
        REQUIRE( a.size() == 4 );

        auto b = a.copy();
        REQUIRE( b.dtype() == Dtype::int32 );
        REQUIRE( b.size() == 4 );
        
        REQUIRE( a.data() != b.data() );
        for (size_t i = 0; i < a.size(); ++i){
            REQUIRE( a[i] == b[i] );
        }
    }

    SECTION("`copy` Test 2"){
        auto a = array<double>({-1, 2, -3, 4, -5.67});
        REQUIRE( a.dtype() == Dtype::float64 );
        REQUIRE( a.size() == 5 );

        auto b = a.copy();
        REQUIRE( b.dtype() == Dtype::float64 );
        REQUIRE( b.size() == 5 );
        
        REQUIRE( a.data() != b.data() );
        for (size_t i = 0; i < a.size(); ++i){
            REQUIRE( a[i] == b[i] );
        }
    }


}

