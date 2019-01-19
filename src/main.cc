
#include <ctime>
#include <iostream>
#include <vector>
#include "CML/Functions/polynomials.h"
#include "CML/LinAlg/matrix.h"

using namespace std;
// using namespace CML;

template <class T>
ostream& operator<<(ostream& out, vector<T>& v) {
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

int main() {
    // Polynomial p1 {{1, 1.3}};
    // Polynomial p2 {{2, 2.2}};
    // // Polynomial p3 {{3, 3.3}};
    // Polynomial p {p1*p2};
    // cout << p << endl;
    // cout << p.getRoots() << endl;
    // Matrix m = createIdentityMatrix(3);
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
