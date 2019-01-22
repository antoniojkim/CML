
#include <ctime>
#include <iostream>
#include <vector>
#include "CML/Functions/polynomials.h"
#include "CML/LinAlg/matrix.h"
#include "CML/LinAlg/eigen.h"

using namespace std;
// using namespace CML;

template <class T>
ostream& operator<<(ostream& out, const vector<T>& v) {
    out << "[";
    for (size_t i = 0; i < v.size(); ++i) {
        if (i > 0) {
            out << " ";
        }
        out << v[i];
    }
    out << "]";
    return out;
}

void matrixTest1(){
    Matrix m1{{{1, 2, 3, 4, 5},
               {4, 5, 6, 7, 8},
               {7, 8, 9, 10, 11},
               {12, 13, 14, 15, 16},
               {17, 18, 19, 20, 21}}};
    printMatrix(cout, m1, "{", "}", ", ") << endl;
    Matrix m2{{{2, 7, 9, 3, 7},
               {4, 8, 3, 7, 5},
               {6, 3, 9, 3, 5},
               {3, 7, 3, 7, 4},
               {0, 4, 7, 5, 3}}};
    printMatrix(cout, m2, "{", "}", ", ") << endl;
    cout << m1*m2 << endl;
    clock_t start = clock();
    for (int i = 0; i<10000000; ++i){
        auto t = m1*m2;
        // t.set(0, 7);
    }
    clock_t end = clock();
    cout << endl << "Took " << double(end-start)/CLOCKS_PER_SEC << " Seconds" << endl;
    // 1.48192 1.49571 1.47836
}

void eigenTest1(){
    Matrix m {{{1.5, -1}, 
               {-1, 11.0/2}}};
    auto evls = eigenvals(m);
    cout << evls << endl;
    cout << m << endl;
    cout << eigenvecs(m) << endl;
}

void eigenTest2(){
    Matrix m {{{1.5, -1, -2},
               {-1, 3.5, -1},
               {-2, -1, 11.0/2}}};
    auto evls = eigenvals(m);
    cout << evls << endl;
    cout << m << endl;
    cout << eigenvecs(m, evls) << endl;
}

void eigenTest3(){
    Matrix m {{{1.3, -3, -2.2},
               {-3, 3.1, -3},
               {-2.2, -3, 4.4}}};
    auto evls = eigenvals(m);
    cout << evls << endl;
    cout << m << endl;
    cout << eigenvecs(m, evls) << endl;
}

int main() {}
