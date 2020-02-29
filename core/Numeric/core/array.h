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
            Array(const std::vector<std::size_t>& shape);
            Array(const Array<T>&);
            Array(Array<T>&&);
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
            T& get(long index);
            inline T& operator[](long index){ return get(index); }


            // Methods
            bool all();
            void all(bool& out);
            // Array<T> all(int axis);
            // void all(int axis, Array<T>& out);
            
            bool any();
            void any(bool& out);
            // std::unique_ptr<Array<T>> any(int axis);
            // void any(int axis, Array<T>& out);

            size_t argmax();
            void argmax(size_t& out);
            // std::unique_ptr<Array<size_t>> argmax(int axis);
            // void argmax(int axis, Array<size_t>& out);

            size_t argmin();
            void argmin(size_t& out);
            // std::unique_ptr<Array<size_t>> argmin(int axis);
            // void argmin(int axis, Array<size_t>& out);

            std::vector<size_t> argsort();
            // std::vector<size_t> argsort(int axis);

            Array<T> copy();

            

    };

    template<typename T = float>
    Array<T> array();
    template<typename T = float>
    Array<T> array(const std::vector<std::size_t>& shape);
    template<typename T = float>
    Array<T> array(std::initializer_list<T> l);


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
