#include <iostream>

#include <Catch2>

using namespace std;

#include <Numeric/array.h>
#include <Numeric/dtypes.h>

using namespace numeric;

TEST_CASE("Array `std` tests", "[std]"){

    using numeric::array;

    SECTION("`Empty Array Test"){
        Array<int> a;
        REQUIRE( a.dtype() == Dtype::int32 );
        REQUIRE( a.size() == 0 );
        REQUIRE( a.ndim() == 1 );
        try{
            a.std();
            REQUIRE( false );
        } catch (numeric::Exception& e){
            REQUIRE( true );
        }
    }

    SECTION("`std` Test (all equal)"){
        auto a = array<int>({1, 1, 1, 1});
        REQUIRE( a.dtype() == Dtype::int32 );
        REQUIRE( a.size() == 4 );
        REQUIRE( a.std() == 0 );
    }

    SECTION("`std` Test (some equal)"){
        auto a = array<float>({0, 1, 0, 1});
        REQUIRE( a.dtype() == Dtype::float32 );
        REQUIRE( a.size() == 4 );
        REQUIRE( a.ndim() == 1 );
        REQUIRE( a.std() == 0.5 );
    }

    SECTION("`std` Test (some negatives)"){
        auto a = array<double>({1, -1, 7, -4, 5});
        REQUIRE( a.dtype() == Dtype::float64 );
        REQUIRE( a.size() == 5 );
        REQUIRE( a.ndim() == 1 );
        REQUIRE( a.std() == 3.97994974842648 );
    }

    SECTION("`std` Test (some negatives, ddof=1)"){
        auto a = array<double>({1, -1, 7, -4, 5});
        REQUIRE( a.dtype() == Dtype::float64 );
        REQUIRE( a.size() == 5 );
        REQUIRE( a.ndim() == 1 );
        REQUIRE( a.std(1) == 4.449719092257398 );
    }

    SECTION("`std` Test (some negatives, ddof=-1)"){
        auto a = array<double>({1, -1, 7, -4, 5});
        REQUIRE( a.dtype() == Dtype::float64 );
        REQUIRE( a.size() == 5 );
        REQUIRE( a.ndim() == 1 );
        REQUIRE( a.std(-1) == 3.6331804249169903 );
    }

}

