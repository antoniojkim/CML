
#include "matrix.h"
#include <stdlib.h>
#include <utility>

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
double* Matrix::operator[](const unsigned int& row) { return m + (row * c); }

double Matrix::get(const unsigned int& i) {
    if (i < r * c) {
        return m[i];
    }
    throw "Index Out of Bounds";
}
double Matrix::get(const unsigned int& row, const unsigned int& col) {
    if (row < r && col < c) {
        return m[row * c + col];
    }
    throw "Index Out of Bounds";
}
void Matrix::set(const unsigned int& i, const double& val) {
    if (i < r * c) {
        m[i] = val;
    }
}
void Matrix::set(const unsigned int& row, const unsigned int& col,
                 const double& val) {
    if (row < r && col < c) {
        m[row * c + col] = val;
    }
}
unsigned int Matrix::getR() const { return r; }
unsigned int Matrix::getC() const { return c; }

void Matrix::swapRows(const unsigned int& r1, const unsigned int& r2) {
    if (r1 < r && r2 < r) {
        for (int i = 0; i < c; ++i) {
            std::swap(m[r1 * c + i], m[r2 * c + i]);
        }
    }
}
void Matrix::swapCols(const unsigned int& c1, const unsigned int& c2) {
    if (c1 < c && c2 < c) {
        for (int i = 0; i < r; ++i) {
            std::swap(m[i * c + c1], m[i * c + c2]);
        }
    }
}
void Matrix::rowMul(const unsigned int& row, const double& val) {
    if (row < r) {
        for (int i = 0; i < c; ++i) {
            m[row * c + i] *= val;
        }
    }
}

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
Matrix Matrix::operator*(const double& val) {
    Matrix product{r, c};
    for (unsigned int i = 0; i < r * c; i++) {
        product.set(i, m[i] * val);
    }
    return product;
}
Matrix operator*(const double& val, Matrix& m) { return m * val; }
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

std::ostream& printMatrix(std::ostream& out, const Matrix& matrix,
                          const string& left, const string& right,
                          const string& delim) {
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

int getFirstNonZeroColumn(Matrix& matrix) {
    auto m = matrix.getM();
    for (unsigned int c = 0; c < matrix.getC(); ++c) {
        for (unsigned int r = 0; r < matrix.getR(); ++r) {
            if (m[r * matrix.getC() + c] != 0) {
                return c;
            }
        }
    }
    return -1;
}
Matrix rowReduce(Matrix& matrix, const bool& showSteps, std::ostream& out) {
    Matrix& reduced{matrix};
    int firstNonZeroColumn = getFirstNonZeroColumn(reduced) - 1;
    for (unsigned int row = 0; row < reduced.getR(); row++) {
        firstNonZeroColumn++;
        if (firstNonZeroColumn >= reduced.getC()) {
            break;
        }

        double factor = reduced.get(row, firstNonZeroColumn);
        if (factor == 0) {
            for (unsigned int restof_rows = row + 1; restof_rows < reduced.getR();
                 restof_rows++) {
                if (reduced.get(restof_rows, firstNonZeroColumn) != 0) {
                    reduced.swapRows(row, restof_rows);
                    factor = reduced.get(row, firstNonZeroColumn);
                    if (factor != 0 || row == reduced.getR() - 1) {
                        break;
                    } else {
                        restof_rows = row;
                    }
                }
            }
            factor = reduced.get(row, firstNonZeroColumn);
            if (factor == 0) {
                if (firstNonZeroColumn < reduced.getC() - 1) {
                    row--;
                }
                continue;
            }
        }
        if (factor != 1) {
            double reciprocal = 1.0 / factor;
            reduced.rowMul(row, reciprocal);
            if (showSteps) {
                out << "Multiplying row " << row << " by " << reciprocal
                    << endl;
                out << reduced << endl;
            }
        }
        for (unsigned int restof_row = 0; restof_row < reduced.getR(); restof_row++) {
            if (row != restof_row) {
                double multiple = reduced.get(restof_row, firstNonZeroColumn);
                if (multiple != 0) {
                    multiple *= -1;
                    for (unsigned int c = 0; c < reduced.getC(); ++c) {
                        reduced.set(restof_row, c,
                                    reduced.get(restof_row, c) +
                                        reduced.get(row, c) * multiple);
                        if (showSteps) {
                            out << "row" << restof_row << " = row" << restof_row
                                << " + row" << row << " * " << multiple << endl;
                            out << reduced << endl;
                        }
                    }
                    // reduced.putRow(restof_row,
                    //                reduced.getRow(restof_row)
                    //                    .add(reduced.getRow(row).mul(multiple)));
                }
            }
        }
    }
    return reduced;
}

Matrix createIdentityMatrix(const unsigned int& d) {
    Matrix matrix{d, d};
    double* m = matrix.getM();
    for (unsigned int i = 0; i < d; ++i) {
        m[d * i + i] = 1;
    }
    return matrix;
}
