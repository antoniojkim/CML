#pragma once

#include <iterator>
#include <memory>

#include "dtypes.h"

namespace numeric {

    class ArrayIter;

    // Multidimensional Array interface;
    class Array {

        struct array_attributes;
        std::unique_ptr<array_attributes> a;

        public:

            Array(Dtype dtype = Dtype::float32);
            ~Array();

            ArrayIter begin();
            ArrayIter end();

            // Attributes
            std::shared_ptr<void *> data();
            Dtype dtype();
            const std::vector<int>& shape();
            uint64_t size();


    };

    Array array(Dtype dtype = Dtype::float32);


    class ArrayIter: public std::iterator<std::input_iterator_tag, Array*>{
        Array* array;
        int index = 0;

        public:

    };

}

namespace std {
    template <> numeric::ArrayIter begin(numeric::Array& a);
    template <> numeric::ArrayIter end(numeric::Array& a);
}
