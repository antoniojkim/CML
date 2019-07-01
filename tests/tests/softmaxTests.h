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
    using Function::CrossEntropyLoss;

    auto x = make_tensor<float>({{1}, {2}}, true);
    auto z = make_tensor<float>({0});

    auto loss = CrossEntropyLoss<float>(x, z);
    assert_equals(loss->item(), 1.3132617f);

    loss->backward();
    assert_equals(x->gradient()->data(0, 0), -0.7310585976f);
    assert_equals(x->gradient()->data(1, 0), 0.731058538f);
}

void softmaxTest3(){
    using namespace std;
    using namespace cml;
    using namespace cml::nn;
    using Function::CrossEntropyLoss;

    auto x = make_tensor<float>({{0.61579928, 0.07365664}
                                , {0.46059955, 0.84609722}
                                , {0.22933349, 0.71500119}}, true);
    cout << x << endl;
    auto z = make_tensor<float>({1, 1});

    auto loss = CrossEntropyLoss<float>(x, z);
    assert_equals(loss->item(), 0.9676999434641942f);

    loss->backward();
    assert_equals(x->gradient()->data(0, 0), 0.1971843564f);
    assert_equals(x->gradient()->data(0, 1), 0.0987346897f);
    assert_equals(x->gradient()->data(1, 0), -0.3311620501f);
    assert_equals(x->gradient()->data(1, 1), -0.2862350747f);
    assert_equals(x->gradient()->data(2, 0), 0.1339776937f);
    assert_equals(x->gradient()->data(2, 1), 0.1875003850f);
}

void softmaxTests(){
    softmaxTest();
    softmaxTest2();
    softmaxTest3();

    using namespace std;
    cout << "All Softmax Tests Passed!" << endl << endl;
}

#endif // __CML_TESTS_SOFTMAX_TESTS_H__
