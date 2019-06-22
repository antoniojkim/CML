#ifndef __CML_TESTS_SOFTMAX_TESTS_H__
#define __CML_TESTS_SOFTMAX_TESTS_H__

#ifndef assert_equals
#define assert_equals(x, y) (assert(int(x*1e6) == int(y*1e6)))
#endif

#include "../core/CML/Tensor.h"
#include "../core/CML/Functions.h"

using namespace std;
using namespace cml;
using namespace cml::nn;

void softmaxTest(){
    using Function::Softmax;
    using Function::MSELoss;

    auto x = make_tensor<float>({{1}, {2}}, true);
    auto y = Softmax<float>(x);
    assert(y->data(0, 0) == 0.26894142f);
    assert(y->data(1, 0) == 0.73105858f);
    auto z = make_tensor<float>({{0}, {1}});

    auto loss = MSELoss<float>(y, z);
    // Weird comparison due to floating point error
    assert_equals(loss->data(0, 0), 0.0723295f);

    loss->backward();
    assert_equals(x->graph()->gradient->data(0, 0), 0.105754f);
    assert_equals(x->graph()->gradient->data(1, 0), -0.105754f);

    cout << "All Softmax Tests Passed!" << endl;
}

void softmaxTests(){
    softmaxTest();
}

#endif // __CML_TESTS_SOFTMAX_TESTS_H__
