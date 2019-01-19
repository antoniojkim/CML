
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
    double get(const unsigned int& i);
    double get(const unsigned int& i, const unsigned int& j);
    void set(const unsigned int& i, const double& val);
    void set(const unsigned int& i, const unsigned int& j, const double& val);
    unsigned int getR() const ;
    unsigned int getC() const ;

    bool isSquare();

    Matrix operator*(Matrix& other);
    Matrix operator+(Matrix& other);
    Matrix operator-(Matrix& other);
};


std::ostream& printMatrix(std::ostream& out, const Matrix& matrix, const std::string& left="[", const std::string& right="]", const std::string& delim=" ");
std::ostream& operator<<(std::ostream& out, const Matrix& matrix);
// std::ostream& operator<<(std::ostream& out, const Matrix& matrix);

Matrix createIdentityMatrix(const unsigned int& d);

// }

#endif // CML_LINALG_MATRIX_H
