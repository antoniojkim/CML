
#include <Eigen/Dense>
#include <ctime>
#include <iostream>
#include <vector>
#include "CML/Functions/polynomials.h"
#include "CML/LinAlg/eigen.h"
#include "CML/LinAlg/matrix.h"

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

void matrixTest1() {
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
    cout << m1 * m2 << endl;
    clock_t start = clock();
    for (int i = 0; i < 10000000; ++i) {
        auto t = m1 * m2;
        // t.set(0, 7);
    }
    clock_t end = clock();
    cout << endl
         << "Took " << double(end - start) / CLOCKS_PER_SEC << " Seconds"
         << endl;
    // 1.48192 1.49571 1.47836
}

void matrixTest2(){
    using Eigen::MatrixXd;
    MatrixXd A(5, 5);
    double a[5][5] = {{1, 2, 3, 4, 5},
                      {4, 5, 6, 7, 8},
                      {7, 8, 9, 10, 11},
                      {12, 13, 14, 15, 16},
                      {17, 18, 19, 20, 21}};
    MatrixXd B(5, 5);
    double b[5][5] = {{2, 7, 9, 3, 7},
                      {4, 8, 3, 7, 5},
                      {6, 3, 9, 3, 5},
                      {3, 7, 3, 7, 4},
                      {0, 4, 7, 5, 3}};
    for (int i = 0; i<5; ++i){
        for (int j = 0; j<5; ++j){
            A(i, j) = a[i][j];
            B(i, j) = b[i][j];
        }
    }

    cout << "[" << endl << A << "]" << endl;
    cout << "[" << endl << B << "]" << endl;
    
    cout << A*B << endl;
    clock_t start = clock();
    for (int i = 0; i < 10000000; ++i) {
        MatrixXd t = A * B;
        t(0, 0) = 7;
    }
    clock_t end = clock();
    cout << endl
         << "Took " << double(end - start) / CLOCKS_PER_SEC << " Seconds"
         << endl;
    /*
    [[40 80 89 79 63]
    [85 167 182 154 135]
    [130 254 275 229 207]
    [205 399 430 354 327]
    [280 544 585 479 447]]
    */
}

void eigenTest1() {
    Matrix m{{{1.5, -1}, {-1, 11.0 / 2}}};
    auto evls = eigenvals(m);
    cout << evls << endl;
    cout << m << endl;
    cout << eigenvecs(m) << endl;
}

void eigenTest2() {
    Matrix m{{{1.5, -1, -2}, {-1, 3.5, -1}, {-2, -1, 11.0 / 2}}};
    auto evls = eigenvals(m);
    cout << evls << endl;
    cout << m << endl;
    cout << eigenvecs(m, evls) << endl;
}

void eigenTest3() {
    Matrix m{{{1.3, -3, -2.2}, {-3, 3.1, -3}, {-2.2, -3, 4.4}}};
    auto evls = eigenvals(m);
    cout << evls << endl;
    cout << m << endl;
    cout << eigenvecs(m, evls) << endl;
}

int main() {
    using Eigen::MatrixXd;
    MatrixXd A(5, 5);
    double a[5][5] = {{1, 2, 3, 4, 5},
                      {4, 5, 6, 7, 8},
                      {7, 8, 9, 10, 11},
                      {12, 13, 14, 15, 16},
                      {17, 18, 19, 20, 21}};
    for (int i = 0; i<5; ++i){
        for (int j = 0; j<5; ++j){
            A(i, j) = a[i][j];
        }
    }

    cout << "[" << endl << A << "]" << endl;
    
    double * d = A.data();
    for (int i = 0; i<25; ++i){
        cout << d[i] << " ";
    }
    cout << endl;

    MatrixXd AT = A.transpose();
    cout << "[" << endl << AT << "]" << endl;
    
    d = AT.data();
    for (int i = 0; i<25; ++i){
        cout << d[i] << " ";
    }
    cout << endl;
}
