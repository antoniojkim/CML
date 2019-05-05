
#include "roots.h"
#include <cmath>
#include <iostream>

using namespace std;

std::vector<double> quadraticFormula(const double& a, const double& b,
                                     const double& c) {
    double discriminant = b * b - 4 * a * c;
    if (discriminant < 0) {
        return {};
    } else if (discriminant == 0) {
        return {-b / (2 * a)};
    }
    discriminant = sqrt(discriminant);
    return {(-b + discriminant) / (2 * a), (-b - discriminant) / (2 * a)};
}

std::vector<double> cubicFormula(const double& a, const double& b,
                                 const double& c, const double& d) {
    if (d == 0) {
        auto roots = quadraticFormula(a, b, c);
        roots.emplace_back(0);
        return roots;
    }
    // Cardano's Formula
    double Q = (3 * a * c - b * b) / (9 * a * a);
    double R =
        ((9 * b * c - 27 * a * d) * a - 2 * b * b * b) / (54 * a * a * a);
    double Q3_R2 = Q * Q * Q + R * R;
    if (Q3_R2 >= 0) {
        Q3_R2 = sqrt(Q3_R2);
        double e = cbrt(R + Q3_R2) + cbrt(R - Q3_R2) - b / (3 * a);
        if (abs(((a * e + b) * e + c) * e + d) < 1.0E-15) {
            auto roots = quadraticFormula(a, b + a * e, c + e * (b + a * e));
            roots.emplace_back(e);
#ifdef DEBUG
            cout << "Cardano's Formula" << endl;
#endif
            return roots;
        }
#ifdef DEBUG
        cout << "Cardano's Formula" << endl;
#endif
        return {e};
    }
    // Rational Root Test
    if (fmod(a, 1) == 0 && fmod(b, 1) == 0 && fmod(c, 1) == 0 &&
        fmod(d, 1) == 0) {
        for (int m = 1; m <= abs(d); m++) {
            for (int n = 1; n <= abs(a); n++) {
                double e = (double)m / n;
                if (abs(((a * e + b) * e + c) * e + d) < 1.0E-15) {
                    auto roots =
                        quadraticFormula(a, b + a * e, c + e * (b + a * e));
                    roots.emplace_back(e);
#ifdef DEBUG
                    cout << "Rational Root Test" << endl;
#endif
                    return roots;
                }
                if (abs(((-a * e + b) * e - c) * e + d) < 1.0E-15) {
                    e *= -1;
                    auto roots =
                        quadraticFormula(a, b + a * e, c + e * (b + a * e));
                    roots.emplace_back(e);
#ifdef DEBUG
                    cout << "Rational Root Test" << endl;
#endif
                    return roots;
                }
            }
        }
    }
    // Newton's Method
    double xn = -1 * b / (3 * a);
    auto local = quadraticFormula(3 * a, 2 * b, c);
    if (!local.empty()) {
        double x1 = local[0];
        x1 = ((a * x1 + b) * x1 + c) * x1 + d;
        if (local.size() == 2) {
            double x2 = local[1];
            x2 = ((a * x2 + b) * x2 + c) * x2 + d;
            if (x1 > 0 && x2 > 0) {
                xn = local[0] - 1;
            } else if (x1 < 0 && x2 < 0) {
                xn = local[1] + 1;
            } else {
                xn = roundf(local[0] + (local[1] - local[0]) / 2 * 100000) /
                     100000;
            }
        } else {
            if (x1 > 0) {
                xn = local[0] - 1;
            } else {
                xn = local[1] + 1;
            }
        }
    }
    double x = xn;
    int count = 0;
    for (; abs(((a * xn + b) * xn + c) * xn + d) > 1.0E-13 && count < 150;
         count++) {
        x = xn;
        xn =
            x - (((a * x + b) * x + c) * x + d) / ((3 * a * x + 2 * b) * x + c);
    }
    if (count < 150) {
        auto roots = quadraticFormula(a, b + a * xn, c + xn * (b + a * xn));
        roots.emplace_back(xn);
#ifdef DEBUG
        cout << "Newton's Method" << endl;
#endif
        return roots;
    }
    return {};
}
