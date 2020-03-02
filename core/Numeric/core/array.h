#pragma once

#include <cstdlib>
#include <cstdint>
#include <initializer_list>
#include <iostream>
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
            std::shared_ptr<T[]> data() const;
            Dtype dtype() const;
            std::size_t itemsize() const;
            std::uint64_t nbytes() const;
            

            const std::vector<std::size_t>& shape() const;
            std::size_t rows() const;
            std::size_t cols() const;
            std::size_t size() const;
            std::size_t ndim() const;

            ArrayIter<T> flat();


            // Accessor Methods
            virtual T& get(long index) const;
            inline T& operator[](long index) const { return get(index); }
            virtual T& get(const std::vector<long>& indices) const;
            inline T& operator[](const std::vector<long>& indices) const { return get(indices); }
            inline T& get(std::initializer_list<long> indices) const { return get(std::vector<long>(indices)); }
            inline T& operator[](std::initializer_list<long> indices) const { return get(std::vector<long>(indices)); }


            // Methods
            bool all() const;
            void all(bool& out) const;
            // Array<T> all(int axis) const;
            // void all(int axis, Array<T>& out) const;
            
            bool any() const;
            void any(bool& out) const;
            // std::unique_ptr<Array<T>> any(int axis);
            // void any(int axis, Array<T>& out);

            size_t argmax() const;
            void argmax(size_t& out) const;
            // std::unique_ptr<Array<size_t>> argmax(int axis);
            // void argmax(int axis, Array<size_t>& out);

            size_t argmin() const;
            void argmin(size_t& out) const;
            // std::unique_ptr<Array<size_t>> argmin(int axis);
            // void argmin(int axis, Array<size_t>& out);

            std::vector<size_t> argsort() const;
            // std::vector<size_t> argsort(int axis);

            Array<T> copy() const;

            Array<T> cumprod() const;
            // Array<T> cumprod(int axis);
            void cumprod(Array<T>& out) const;
            // void cumprod(int axis, Array<T>& out);

            Array<T> cumsum() const;
            // Array<T> cumsum(int axis);
            void cumsum(Array<T>& out) const;
            // void cumsum(int axis, Array<T>& out);

            Array<T> dot(const Array<T>& other) const;
            void dot(const Array<T>& other, Array<T>& out) const;

            void fill(T value);

            Array<T> zero() const;
            

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


template<typename T = float>
bool operator==(const numeric::Array<T>& a1, const numeric::Array<T>& a2);

template<typename T = float>
std::ostream& operator<<(std::ostream&, const numeric::Array<T>&);
