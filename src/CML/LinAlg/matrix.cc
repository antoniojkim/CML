
#include "matrix.h"
#include <stdlib.h>

using namespace std;
// using namespace CML;

Matrix::Matrix(const unsigned int& r, const unsigned int& c) : r{r}, c{c} {
    m = (double*)calloc(r * c, sizeof(double));  // set to zero
}
Matrix::Matrix(std::vector<std::vector<double>> v) {
    r = v.size();
    if (r > 0) {
        c = v[0].size();
        m = (double*)calloc(r * c, sizeof(double));  // set to zero
        for (unsigned int i = 0; i < r; ++i) {
            if (v[i].size() != c) {
                throw "Non Rectangular Matrix";
            }
            for (unsigned int j = 0; j < c; ++j) {
                m[i * c + j] = v[i][j];
            }
        }
    }
}
Matrix::Matrix(const Matrix& other) : r{other.r}, c{other.c} {
    m = (double*)calloc(r * c, sizeof(double));  // set to zero
    for (unsigned int i = 0; i < r * c; ++i) {
        m[i] = other.m[i];
    }
}
Matrix::Matrix(Matrix&& other) : r{other.r}, c{other.c} {
    m = other.m;
    other.m = nullptr;
}
Matrix::~Matrix() { delete m; }

double* Matrix::getM() const { return m; }
double Matrix::get(const unsigned int& i) {
    if (i < r * c) {
        return m[i];
    }
    throw "Index Out of Bounds";
}
double Matrix::get(const unsigned int& i, const unsigned int& j) {
    if (i < r && j < c) {
        return m[i * c + j];
    }
    throw "Index Out of Bounds";
}
void Matrix::set(const unsigned int& i, const double& val) {
    if (i < r * c) {
        m[i] = val;
    }
}
void Matrix::set(const unsigned int& i, const unsigned int& j,
                 const double& val) {
    if (i < r && j < c) {
        m[i * c + j] = val;
    }
}
unsigned int Matrix::getR() const { return r; }
unsigned int Matrix::getC() const { return c; }

bool Matrix::isSquare() { return r == c; }

Matrix Matrix::operator*(Matrix& other) {
    if (r == other.c) {
        Matrix product{r, other.c};
        double sum = 0;
        for (unsigned int i = 0; i < r; i++) {
            for (unsigned int j = 0; j < product.c; j++) {
                sum = 0;
                for (unsigned int k = 0; k < c; k++) {
                    sum += m[i * product.c + k] * other.m[k * product.c + j];
                }
                product.m[i * product.c + j] = sum;
            }
        }
        return product;
    } else if (r == other.r && c == other.c) {
        Matrix product{r, c};
        for (unsigned int i = 0; i < r * c; i++) {
            product.set(i, m[i] * other.m[i]);
        }
        return product;
    }
    throw "Dimensions don't match";
}
Matrix Matrix::operator+(Matrix& other) {
    if (r == other.r && c == other.c) {
        Matrix product{r, c};
        for (unsigned int i = 0; i < r * c; i++) {
            product.set(i, m[i] + other.m[i]);
        }
        return product;
    }
    throw "Dimensions don't match";
}
Matrix Matrix::operator-(Matrix& other) {
    if (r == other.r && c == other.c) {
        Matrix product{r, c};
        for (unsigned int i = 0; i < r * c; i++) {
            product.set(i, m[i] - other.m[i]);
        }
        return product;
    }
    throw "Dimensions don't match";
}

std::ostream& printMatrix(std::ostream& out, const Matrix& matrix, const string& left,
                          const string& right, const string& delim) {
    for (unsigned int i = 0; i < matrix.getR(); ++i) {
        if (i == 0) {
            out << left;
        } else {
            out << " ";
        }
        out << left;
        for (unsigned int j = 0; j < matrix.getC(); ++j) {
            if (j > 0) {
                out << delim;
            }
            out << matrix.getM()[i * matrix.getC() + j];
        }
        out << right;
        if (i + 1 < matrix.getR()) {
            out << delim << endl;
        }
    }
    out << right;
    return out;
}
std::ostream& operator<<(std::ostream& out, const Matrix& matrix) {
    return printMatrix(out, matrix);
}

Matrix createIdentityMatrix(const unsigned int& d) {
    Matrix matrix{d, d};
    double* m = matrix.getM();
    for (unsigned int i = 0; i < d; ++i) {
        m[d * i + i] = 1;
    }
    return matrix;
}
