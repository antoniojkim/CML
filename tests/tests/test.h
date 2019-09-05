#ifndef __CML_TESTS_TEST_H__
#define __CML_TESTS_TEST_H__

#include <cassert>
#include <iostream>

#include "../../core/CML/Functions.h"
#include "../../core/CML/Tensor.h"
#include "../../core/CML/optim/Optimizer.h"
#include "../../core/Utils/Exceptions.h"

namespace cml {

    template<typename T, typename U>
    void assert_equals(const T& x, const U& y){
        if (int(x*1e6) != int(y*1e6)){
            throw AssertionFailedException(x, "!=", y);
        }
    }

}

#endif // __CML_TESTS_TEST_H__
