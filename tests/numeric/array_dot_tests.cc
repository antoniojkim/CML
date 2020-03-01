#include <iostream>

#include <Catch2>

using namespace std;

#include <Numeric/array.h>
#include <Numeric/dtypes.h>

using namespace numeric;

TEST_CASE("Array `dot` tests", "[dot]"){

    using numeric::array;

    SECTION("Empty Array Test"){
        try {
            Array a1;
            a1.fill(2);
            REQUIRE( a1.dtype() == Dtype::float32 );
            REQUIRE( a1.size() == 0 );
            REQUIRE( a1.ndim() == 1 );

            Array a2;
            a2.fill(3);
            REQUIRE( a2.dtype() == Dtype::float32 );
            REQUIRE( a2.size() == 0 );
            REQUIRE( a2.ndim() == 1 );

            auto a3 = a1.dot(a2);
            REQUIRE( false );
        } catch(numeric::Exception& e){
            REQUIRE( true );
        }
    }

    SECTION("Basic Dot Test"){
        Array a1 (vector<size_t>{3, 2});
        REQUIRE( a1.dtype() == Dtype::float32 );
        REQUIRE( a1.size() == 6 );
        REQUIRE( a1.ndim() == 2 );

        Array a2 (vector<size_t>{2, 3});
        REQUIRE( a2.dtype() == Dtype::float32 );
        REQUIRE( a2.size() == 6 );
        REQUIRE( a2.ndim() == 2 );

        auto a3 = a1.dot(a2);
        REQUIRE( a3.dtype() == Dtype::float32 );
        REQUIRE( a3.shape() == vector<size_t>{3, 3} );
        REQUIRE( a3.size() == 9 );
        REQUIRE( a3.ndim() == 2 );
    }

    // SECTION("`dot` Test (int)"){
    //     auto a = array<int>({1, 2, 3});
    //     REQUIRE( a.dtype() == Dtype::int32 );
    //     REQUIRE( a.size() == 3 );
    //     REQUIRE( a.dot() == array<int>({1, 3, 6}) );
    // }

    // SECTION("`dot` Test 2 (int)"){
    //     auto a = array<int>({1, 2, 3, 4, 5, 6});
    //     REQUIRE( a.dtype() == Dtype::int32 );
    //     REQUIRE( a.size() == 6 );
    //     REQUIRE( a.dot() == array<int>({1, 3, 6, 10, 15, 21}) );
    // }

    // SECTION("`dot` Test (some negatives)"){
    //     auto a = array<int>({1, -1, 2, -4, 5});
    //     REQUIRE( a.dtype() == Dtype::int32 );
    //     REQUIRE( a.size() == 5 );
    //     REQUIRE( a.dot() == array<int>({1, 0, 2, -2, 3}) );
    // }

    // SECTION("`dot` Test (some negatives and zero)"){
    //     auto a = array<int>({1, -1, 2, -4, 0});
    //     REQUIRE( a.dtype() == Dtype::int32 );
    //     REQUIRE( a.size() == 5 );
    //     REQUIRE( a.dot() == array<int>({1, 0, 2, -2, -2}) );
    // }

    // SECTION("`dot` Test (positive, negative floats)"){
    //     auto a = array<float>({1.0, -1.0, 2.0, -4.0, 5.0});
    //     REQUIRE( a.dtype() == Dtype::float32 );
    //     REQUIRE( a.size() == 5 );
    //     REQUIRE( a.ndim() == 1 );
    //     REQUIRE( a.dot() == array<float>({1, 0, 2, -2, 3}) );
    // }

    // SECTION("`dot` Test (floats with zero)"){
    //     auto a = array({1.0, -1.0, 2.0, -4.0, 0.0});
    //     REQUIRE( a.dtype() == Dtype::float64 );
    //     REQUIRE( a.size() == 5 );
    //     REQUIRE( a.ndim() == 1 );
    //     REQUIRE( a.dot() == array<double>({1, 0, 2, -2, -2}) );
    // }

}

