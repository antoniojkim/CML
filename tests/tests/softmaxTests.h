#ifndef __CML_TESTS_SOFTMAX_TESTS_H__
#define __CML_TESTS_SOFTMAX_TESTS_H__

#include "test.h"


void softmaxTest(){
    using namespace cml;
    using namespace cml::nn;
    using Function::Softmax;
    using Function::MSELoss;

    auto x = make_tensor<float>({{1}, {2}}, true);
    auto y = Softmax<float>(x);
    assert(y->data(0, 0) == 0.26894142f);
    assert(y->data(1, 0) == 0.73105858f);
    auto z = make_tensor<float>({{0}, {1}});

    auto loss = MSELoss<float>(y, z);
    assert_equals(loss->data(0, 0), 0.0723295f);

    loss->backward();
    assert_equals(x->gradient()->data(0, 0), 0.105754f);
    assert_equals(x->gradient()->data(1, 0), -0.105754f);
}

void softmaxTest2(){
    using namespace std;
    using namespace cml;
    using namespace cml::nn;
    using Function::Softmax;
    using Function::CrossEntropyLoss;

    auto x = make_tensor<float>({{1}, {2}}, true);
    auto z = make_tensor<float>({0});

    auto loss = CrossEntropyLoss<float>(x, z);
    assert_equals(loss->item(), 1.3132617f);

    loss->backward();
    assert_equals(x->gradient()->data(0, 0), -0.7310585976f);
    assert_equals(x->gradient()->data(1, 0), 0.731058538f);
    
    
}

void softmaxTests(){
    softmaxTest();
    softmaxTest2();

    using namespace std;
    cout << "All Softmax Tests Passed!" << endl << endl;
}

#endif // __CML_TESTS_SOFTMAX_TESTS_H__
