#include <iostream>
#include <sstream>

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

    SECTION("Simple 1D Array Print Test "){
        Array<int> a (vector<size_t>{10});
        a.fill(3);
        REQUIRE( a.dtype() == Dtype::int32 );
        REQUIRE( a.size() == 10 );
        REQUIRE( a.ndim() == 1 );

        ostringstream oss;
        oss << a;
        REQUIRE( oss.str() == "[ 3 3 3 3 3 3 3 3 3 3]" );
    }

    SECTION("Simple 2D Array Print Test "){
        Array<int> a (vector<size_t>{5, 2});
        REQUIRE( a.dtype() == Dtype::int32 );
        REQUIRE( a.size() == 10 );
        REQUIRE( a.ndim() == 2 );

        for (int i = 0; i < 5; ++i){
            for (int j = 0; j < 2; ++j){
                a[{i, j}] = i * (j + 1);
            }
        }

        REQUIRE( a[{4, 1}] == 8 );

        ostringstream oss;
        oss << a;
        REQUIRE( oss.str() == "[[ 0 0]\n [ 1 2]\n [ 2 4]\n [ 3 6]\n [ 4 8]]");
    }

    SECTION("Simple 3D Array Print Test "){
        Array<int> a (vector<size_t>{5, 2, 3});
        REQUIRE( a.dtype() == Dtype::int32 );
        REQUIRE( a.size() == 30 );
        REQUIRE( a.ndim() == 3 );

        for (int i = 0; i < 5; ++i){
            for (int j = 0; j < 2; ++j){
                for (int k = 0; k < 3; ++k){
                    a[{i, j, k}] = (i * (j + 1) + j) * (k - 3);
                }
            }
        }

        ostringstream oss;
        oss << a;
        REQUIRE( oss.str() == "[[[ 0 0 0]\n  [ -3 -2 -1]]\n [[ -3 -2 -1]\n"
                              "  [ -9 -6 -3]]\n [[ -6 -4 -2]\n  [ -15 -10 -5]]\n"
                              " [[ -9 -6 -3]\n  [ -21 -14 -7]]\n [[ -12 -8 -4]]\n  [ -27 -18 -9]]]");
    }

}

