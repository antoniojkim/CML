#pragma once

#include <cstdlib>
#include <cstdint>
#include <initializer_list>
#include <iterator>
#include <memory>
#include <vector>

#include "dtypes.h"

namespace numeric {

    class ArrayIter;
    struct array_attributes;

    // Multidimensional Array interface;
    class Array {

        std::unique_ptr<array_attributes> a;

        public:

            Array(Dtype dtype = Dtype::float32);
            Array(const std::vector<size_t>& v, Dtype dtype = Dtype::float32);
            template<typename T>
            Array(std::initializer_list<T> l, Dtype dtype = Dtype::float32);
            ~Array();

            ArrayIter begin();
            ArrayIter end();

            // Attributes
            std::shared_ptr<void> data();
            Dtype dtype();
            std::size_t itemsize();
            std::uint64_t nbytes();
            

            const std::vector<std::size_t>& shape();
            std::size_t size();
            std::size_t ndim();

            ArrayIter flat();


            // Methods
            bool all();
            void all(bool& out);
            // template<typename T> Array all(int axis);
            // template<typename T> void all(int axis, Array& out);

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
