
#include "polynomials.h"
#include <cmath>
#include <iterator>
#include "roots.h"

using namespace std;

Poly1d::Poly1d(vector<double> coefficients) {
    this->coefficients.reserve(coefficients.size());
    for (auto c = rbegin(coefficients); c != rend(coefficients); ++c) {
        this->coefficients.emplace_back(*c);
    }
    while (this->coefficients.back() == 0) {
        this->coefficients.pop_back();
    }
}
Poly1d::Poly1d(const Poly1d& other) : coefficients{other.coefficients} {}
Poly1d::Poly1d(const unsigned int& order) {
    coefficients.reserve(order);
    for (unsigned int i = 0; i < order; ++i) {
        coefficients.emplace_back(0);
    }
}

double& Poly1d::operator[](const int& i) { return coefficients[i]; }
double Poly1d::operator()(const double& x) {
    double y = coefficients.back();
    for (int i = coefficients.size() - 2; i >= 0; --i) {
        y = y * x + coefficients[i];
    }
    return y;
}
Poly1d Poly1d::operator*(const Poly1d& other) {
    Poly1d p{(unsigned int)((this->coefficients.size() - 1) + (other.coefficients.size() - 1) + 1)};
    for (size_t i = 0; i < this->coefficients.size(); ++i) {
        for (size_t j = 0; j < other.coefficients.size(); ++j) {
            p[i + j] += this->coefficients[i] * other.coefficients[j];
        }
    }
    return p;
}
Poly1d Poly1d::operator+(const Poly1d& other) {
    Poly1d p{(unsigned int)(max(this->coefficients.size(), other.coefficients.size()) + 1)};
    for (size_t i = 0; i < this->coefficients.size(); ++i) {
        p[i] += this->coefficients[i];
    }
    for (size_t i = 0; i < other.coefficients.size(); ++i) {
        p[i] += other.coefficients[i];
    }
    return p;
}
Poly1d Poly1d::operator-(const Poly1d& other) {
    Poly1d p{(unsigned int)(max(this->coefficients.size(), other.coefficients.size()) + 1)};
    for (size_t i = 0; i < this->coefficients.size(); ++i) {
        p[i] += this->coefficients[i];
    }
    for (size_t i = 0; i < other.coefficients.size(); ++i) {
        p[i] -= other.coefficients[i];
    }
    return p;
}

std::vector<double> Poly1d::getRoots() {
    // std::vector<double> roots;
    // roots.reserve(coefficients.size()-1);
    if (coefficients.size() == 3) {
        double& a = coefficients[2];
        double& b = coefficients[1];
        double& c = coefficients[0];
        return quadraticFormula(a, b, c);
    }
    if (coefficients.size() == 4) {
        double& a = coefficients[3];
        double& b = coefficients[2];
        double& c = coefficients[1];
        double& d = coefficients[0];
        return cubicFormula(a, b, c, d);
    }
    return {};
}
Poly1d Poly1d::getDerivative() {
    Poly1d p{(unsigned int)(coefficients.size() - 1)};
    for (unsigned int i = 1; i < coefficients.size(); ++i) {
        p[i - 1] = i * coefficients[i];
    }
    return p;
}

std::ostream& operator<<(std::ostream& out, const Poly1d& p) {
    for (int i = p.coefficients.size() - 1; i >= 0; --i) {
        if (p.coefficients[i] != 0) {
            if (i < (int)(p.coefficients.size() - 1)) {
                if (p.coefficients[i] > 0) {
                    out << "+";
                }
            }
            if (abs(p.coefficients[i]) != 1 || i == 0) {
                out << p.coefficients[i];
            }
            if (i > 1) {
                out << p.var << "^" << i;
            } else if (i == 1) {
                out << p.var;
            }
        }
    }
    return out;
}
