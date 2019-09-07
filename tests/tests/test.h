#ifndef __CML_TESTS_TEST_H__
#define __CML_TESTS_TEST_H__

#include <algorithm>
#include <cassert>
#include <iostream>

#include "../../core/CML/Functions.h"
#include "../../core/CML/Tensor.h"
#include "../../core/CML/optim/Optimizer.h"
#include "../../core/Utils/Exceptions.h"

namespace cml {

    template<typename T, typename U>
    bool comparator(const T& x, const U& y){
        return int(x*1e6) == int(y*1e6);
    }

    template<typename T, typename U>
    void assert_equals(const T& x, const U& y){
        if (!comparator(x, y)){
            throw AssertionFailedException(x, "!=", y);
        }
    }

    template<typename T>
    void assert_equals(tensor<T> actual, tensor<T> expected){
        if (actual->shape() != expected->shape()){
            throw AssertionFailedException("Tensor shapes do not match:  ", actual->shape(), "!=", expected->shape());
        }
        if (!std::equal(actual->begin(), actual->end(), expected->begin(), comparator<T, T>)){
            throw AssertionFailedException(actual, "!=", expected);
        }
    }

}

#endif // __CML_TESTS_TEST_H__
