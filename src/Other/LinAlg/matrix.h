
#ifndef CML_LINALG_MATRIX_H
#define CML_LINALG_MATRIX_H

#include <iostream>
#include <memory>
#include <string>
#include <vector>

// namespace CML {
class Matrix {
    unsigned int r;
    unsigned int c;
    double* m;

   public:
    Matrix(const unsigned int& r, const unsigned int& c);
    Matrix(std::vector<std::vector<double>> v);
    Matrix(const Matrix& other);
    Matrix(Matrix&& other);
    ~Matrix();

    double* getM() const ;
    double* operator[](const unsigned int& row);

    double get(const unsigned int& i);
    double get(const unsigned int& row, const unsigned int& col);
    void set(const unsigned int& i, const double& val);
    void set(const unsigned int& row, const unsigned int& col, const double& val);
    unsigned int getR() const ;
    unsigned int getC() const ;

    void swapRows(const unsigned int& r1, const unsigned int& r2);
    void swapCols(const unsigned int& c1, const unsigned int& c2);

    void rowMul(const unsigned int& r, const double& val);

    bool isSquare();

    Matrix operator*(Matrix& other);
    Matrix operator*(const double& val);
    Matrix operator+(Matrix& other);
    Matrix operator-(Matrix& other);
};

Matrix createIdentityMatrix(const unsigned int& d);


std::ostream& printMatrix(std::ostream& out, const Matrix& matrix, const std::string& left="[", const std::string& right="]", const std::string& delim=" ");
std::ostream& operator<<(std::ostream& out, const Matrix& matrix);


Matrix operator*(const double& val, Matrix& m);
Matrix rowReduce(Matrix& m, const bool& showSteps=false, std::ostream& out=std::cout);




// }

#endif // CML_LINALG_MATRIX_H
