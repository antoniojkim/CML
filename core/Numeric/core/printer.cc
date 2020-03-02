
#include <iomanip>
#include <cmath>
#include <sstream>

#include "array.h"
#include "dtypes.h"
#include "printer.h"

using namespace std;
using namespace numeric;

int Printer::precision = 8;
int Printer::threshold = 1000;
int Printer::edgeitems = 3;
int Printer::linewidth = 75;
bool Printer::suppress = false;

std::string Printer::nanstr = "NaN";
std::string Printer::infstr = "inf";

char Printer::sign = '-';

std::string Printer::floatmode = "maxprec_equal";

template<typename T>
std::ostream& Printer::stringify(std::ostream& out, T value){
    out << " " << std::fixed << std::setprecision(precision)
        << value;
    return out;
}

template<typename T>
ostream& Printer::print(ostream& out, const Array<T>& array, const std::string& indent){

    // int num_elements_per_line = (linewidth - 7 - shape.size() * 2) / (precision + 2);
    vector<size_t> shape = array.shape();
    vector<long> indices (shape.size(), 0);
    int curr_axis = 0;

    size_t i = 0;
    int num_spaces = 0, num_bracket = 0;
    while(i < array.size()){
        num_spaces = 0;
        num_bracket = 0;
        for (int j = (int) indices.size() - 1; j >= 0; --j){
            if (indices[j] == 0){
                ++num_bracket;
            }
            else {
                num_spaces = j + 1;
                break;
            }
        }
        out << std::setw(num_spaces) << std::setfill(' ') << "";
        out << std::setw(num_bracket) << std::setfill('[') << "";

        for (size_t last_axis = 0; last_axis < shape.back(); ++last_axis){
            indices.back() = last_axis;
            stringify(out, array[indices]);
            ++i;
        }

        for (int j = (int) indices.size() - 1; j >= 0; --j){
            if (indices[j] == (long) shape[j] - 1){
                out << ']';
            }
        }

        indices.back() = 0;

        // Next axis
        for (int j = (int) indices.size() - 2; j >= 0; --j){
            ++indices[j];
            if (indices[j] < (long) shape[j]){
                out << endl;
                break;
            }
            indices[j] = 0;
            ++curr_axis;
        }
    }

    return out;
}

#define PREFIX
#define SUFFIX

#define SELECT(T, _2) \
    template ostream& Printer::print<T>(ostream&, const Array<T>&, const std::string&); \
    template std::ostream& Printer::stringify<T>(std::ostream&, T);

ARRAY_TYPES(PREFIX, SELECT, SUFFIX)
COMPLEX_TYPES(PREFIX, SELECT, SUFFIX)

#undef SELECT

#undef PREFIX
#undef SUFFIX
