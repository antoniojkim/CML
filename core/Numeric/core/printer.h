
#include <iostream>
#include <map>
#include <string>

namespace numeric {

    template<typename T>
    class Array;

    struct Printer {

        static int precision;  // 8
        static int threshold;  // 1000
        static int edgeitems;  // 3
        static int linewidth;  // 75
        static bool suppress;  // false

        static std::string nanstr; // "NaN"
        static std::string infstr; // "inf"

        static char sign;  // '-'

        static std::string floatmode;  // "maxprec_equal"

        template<typename T>
        static std::ostream& stringify(std::ostream&, T value);

        template<typename T>
        static std::ostream& print(std::ostream&, const Array<T>&, const std::string& indent = "");

    };

}
