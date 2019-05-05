
#ifndef CML_FUNCTIONS_Poly1dS_H
#define CML_FUNCTIONS_Poly1dS_H

#include <initializer_list>
#include <iostream>
#include <vector>

class Poly1d {
    std::vector<double> coefficients;
    std::string var = "x";

   public:
    Poly1d(std::vector<double> coefficients);
    Poly1d(const Poly1d& other);
    Poly1d(const unsigned int& order);

    double& operator[](const int&);
    double operator()(const double&);
    Poly1d operator*(const Poly1d&);
    Poly1d operator+(const Poly1d&);
    Poly1d operator-(const Poly1d&);
    
    std::vector<double> getRoots();
    Poly1d getDerivative();
    
    friend std::ostream& operator<<(std::ostream& out, const Poly1d& p);
};


#endif  // CML_FUNCTIONS_Poly1dS_H
