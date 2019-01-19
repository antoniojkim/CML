
#ifndef CML_FUNCTIONS_POLYNOMIALS_H
#define CML_FUNCTIONS_POLYNOMIALS_H

#include <initializer_list>
#include <iostream>
#include <vector>

class Polynomial {
    std::vector<double> coefficients;
    std::string var = "x";

   public:
    Polynomial(std::vector<double> coefficients);
    Polynomial(const Polynomial& other);
    Polynomial(const int& order);

    Polynomial operator*(const Polynomial&);
    
    std::vector<double> getRoots();
    
    friend std::ostream& operator<<(std::ostream& out, Polynomial& p);
};


#endif  // CML_FUNCTIONS_POLYNOMIALS_H
