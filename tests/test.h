#ifndef __CML_TESTS_TEST_H__
#define __CML_TESTS_TEST_H__

#include <cassert>
#include <iostream>

#ifndef assert_equals
#define assert_equals(x, y) (assert(int(x*1e6) == int(y*1e6)))
#endif

#include "../core/CML/Functions.h"
#include "../core/CML/Tensor.h"

#endif // __CML_TESTS_TEST_H__
