// #pragma once

#include <memory>

#include "dtypes.h"

namespace numeric {

    struct array_attributes;
    class ArrayIter;

    // Multidimensional Array interface;
    class Array {

        std::unique_ptr<array_attributes> a;

        public:

            Array(Dtype dtype = Dtype::float32);

            ArrayIter begin();
            ArrayIter end();

            // Attributes
            std::shared_ptr<void *> data();
            Dtype dtype();
            const std::vector<int>& shape();
            uint64_t size();


    };

    Array array(Dtype dtype = Dtype::float32);


    class ArrayIter{
       Array* array;
    };

}

namespace std {
   template <> numeric::ArrayIter begin(numeric::Array& a){
      return a.begin();
   }
   template <> numeric::ArrayIter end(numeric::Array& a){
      return a.end();
   }
}
