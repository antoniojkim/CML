
#include "polynomials.h"
#include "roots.h"
#include <cmath>
#include <iterator>

using namespace std;

Polynomial::Polynomial(vector<double> coefficients) {
    this->coefficients.reserve(coefficients.size());
    for (auto c = std::rbegin(coefficients); c != std::rend(coefficients);
         ++c) {
        this->coefficients.emplace_back(*c);
    }
    while (this->coefficients.back() == 0) {
        this->coefficients.pop_back();
    }
}
Polynomial::Polynomial(const Polynomial& other)
    : coefficients{other.coefficients} {}
Polynomial::Polynomial(const int& order) {
    coefficients.reserve(order);
    for (int i = 0; i < order; ++i) {
        coefficients.emplace_back(0);
    }
}

Polynomial Polynomial::operator*(const Polynomial& other) {
    Polynomial p{(this->coefficients.size() - 1) +
                 (other.coefficients.size() - 1) + 1};
    for (size_t i = 0; i < this->coefficients.size(); ++i) {
        for (size_t j = 0; j < other.coefficients.size(); ++j) {
            p.coefficients[i + j] +=
                this->coefficients[i] * other.coefficients[j];
        }
    }
    return p;
}

std::vector<double> Polynomial::getRoots() {
    // std::vector<double> roots;
    // roots.reserve(coefficients.size()-1);
    if (coefficients.size() == 3){
        double& a = coefficients[2];
        double& b = coefficients[1];
        double& c = coefficients[0];
        return quadraticFormula(a, b, c);
    }
    if (coefficients.size() == 4){
        double& a = coefficients[3];
        double& b = coefficients[2];
        double& c = coefficients[1];
        double& d = coefficients[0];
        return cubicFormula(a, b, c, d);
    }
    return {};
}

std::ostream& operator<<(std::ostream& out, Polynomial& p) {
    for (int i = p.coefficients.size() - 1; i >= 0; --i) {
        if (p.coefficients[i] != 0) {
            if (i < p.coefficients.size() - 1) {
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
