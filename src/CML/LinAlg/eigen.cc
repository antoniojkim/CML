
#include "eigen.h"
#include "../Functions/roots.h"
#include <cmath>

using namespace std;

double det(Matrix& m) {}

vector<double> eigenvals(Matrix& matrix) {
    if (matrix.isSquare()) {
        auto m = matrix.getM();
        if (matrix.getR() == 2) {
            double a = m[0];
            double b = m[2];
            double c = m[1];
            double d = m[3];
            return quadraticFormula(1.0, -(a + d), a * d - b * c);
        }
        if (matrix.getR() == 3) {
            double a = m[0];
            double b = m[3];
            double c = m[6];
            double d = m[1];
            double e = m[4];
            double f = m[7];
            double g = m[2];
            double h = m[5];
            double i = m[8];
            return cubicFormula(-1, i + e + a,
                                f * h - e * i + c * g + b * d - a * i - a * e,
                                c * d * h - c * e * g + b * f * g - b * d * i -
                                    a * f * h + a * e * i);
        }
    }
    return {};
}
vector<vector<double>> eigenvecs(Matrix& m) {
    auto evls = eigenvals(m);
    return eigenvecs(m, evls);
}

void normalize(vector<double>& v){
    double sum = 0;
    for (auto& e : v){
        sum += e*e;
    }
    sum = sqrt(sum);
    for (auto& e : v){
        e /= sum;
    }
}
vector<vector<double>> eigenvecs(Matrix& matrix, vector<double>& evls) {
    if (matrix.isSquare() && evls.size() == matrix.getR()) {
        auto m = matrix.getM();
        vector<vector<double>> eigvecs;
        if (matrix.getR() == 2) {
            eigvecs.reserve(2);
            for (auto& eig : evls) {
                double a = matrix[0][0]-eig;
                double b = matrix[0][1];
                eigvecs.emplace_back(vector<double>{-b/a, 1});
            }
        }
        else if (matrix.getR() == 3){
            eigvecs.reserve(3);
            for (auto& eig : evls) {
                double a = matrix[0][0]-eig;
                double b = matrix[0][1];
                double c = matrix[0][2];
                double d = matrix[1][0];
                double e = matrix[1][1]-eig;
                double f = matrix[1][2];

                double factor = -d/a;
                e += b*factor;
                f += c*factor;

                eigvecs.emplace_back(vector<double>{(b*f/e-c)/a, -f/e, 1});
            }
        }
        for (auto& v : eigvecs){
            normalize(v);
        }
        return eigvecs;
    }
    return {};
}
