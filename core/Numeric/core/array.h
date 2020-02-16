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
            const long size();


    };

}

namespace std {
   template <> ArrayIter begin<numeric::Array>(numeric::Array& a){
      return a.begin();
   }
   template <> ArrayIter end<numeric::Array>(numeric::Array& a){
      return a.end();
   }
}
