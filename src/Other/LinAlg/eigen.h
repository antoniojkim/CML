
#ifndef CML_LINALG_EIGEN_H
#define CML_LINALG_EIGEN_H

#include "matrix.h"
#include <vector>

double det(Matrix& m);

std::vector<double> eigenvals(Matrix& m);
std::vector<std::vector<double>> eigenvecs(Matrix& m);
std::vector<std::vector<double>> eigenvecs(Matrix& m, std::vector<double>& evls);

#endif // CML_LINALG_EIGEN_H
