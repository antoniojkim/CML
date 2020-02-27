#pragma once

#include <cstdlib>
#include <cstdint>
#include <initializer_list>
#include <iterator>
#include <memory>
#include <vector>

#include "dtypes.h"

namespace numeric {

    template<typename T>
    class ArrayIter;
    
    template<typename T>
    struct array_attributes;

    // Multidimensional Array interface;
    template<typename T = float>
    class Array {

        std::unique_ptr<array_attributes<T>> a;

        public:

            Array();
            Array(const std::vector<size_t>& v);
            template<typename U>
            Array(std::initializer_list<U> l);
            ~Array();

            ArrayIter<T> begin();
            ArrayIter<T> end();

            // Attributes
            std::shared_ptr<T[]> data();
            Dtype dtype();
            std::size_t itemsize();
            std::uint64_t nbytes();
            

            const std::vector<std::size_t>& shape();
            std::size_t size();
            std::size_t ndim();

            ArrayIter<T> flat();


            // Accessor Methods



            // Methods
            bool all();
            void all(bool& out);
            // template<typename T> Array all(int axis);
            // template<typename T> void all(int axis, Array& out);
            
            bool any();
            void any(bool& out);
            // template<typename T> Array any(int axis);
            // template<typename T> void any(int axis, Array& out);

            

    };

    template<typename T = float>
    Array<T> array();


    template<typename T>
    class ArrayIter: public std::iterator<std::input_iterator_tag, Array<T>*>{
        Array<T>* array;
        int index = 0;

        public:

    };

}

namespace std {
    template<typename T>
    numeric::ArrayIter<T> begin(numeric::Array<T>& a);
    template<typename T>
    numeric::ArrayIter<T> end(numeric::Array<T>& a);
}
