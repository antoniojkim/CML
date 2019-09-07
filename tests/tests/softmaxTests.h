#ifndef __CML_TESTS_SOFTMAX_TESTS_H__
#define __CML_TESTS_SOFTMAX_TESTS_H__

#include "test.h"


void softmaxTest(){
    using namespace cml;
    using namespace cml::nn;
    using Function::Softmax;
    using Function::MSELoss;

    auto x = make_tensor<float, 2, 1>({{1}, {2}}, true);
    auto y = Softmax<float>(x);
    assert_equals(y, make_tensor<float, 2, 1>({{0.2689414322}, {0.7310585976}}));
    auto z = make_tensor<float, 2, 1>({{0}, {1}});

    auto loss = MSELoss(y, z);
    assert_equals(loss->item(), 0.0723295f);

    loss->backward();
    assert_equals(x->gradient()->at(0, 0), 0.105754f);
    assert_equals(x->gradient()->at(1, 0), -0.105754f);
}

void softmaxTest2(){
    using namespace std;
    using namespace cml;
    using namespace cml::nn;
    using Function::CrossEntropyLoss;

    auto x = make_tensor<float, 1, 2>({{1, 2}}, true);
    auto z = make_scalar<float>(0);

    auto loss = CrossEntropyLoss(x, z);
    assert_equals(loss->item(), 1.3132617f);

    loss->backward();
    assert_equals(x->gradient()->at(0, 0), -0.7310585976f);
    assert_equals(x->gradient()->at(0, 1), 0.731058538f);
}

void softmaxTest3(){
    using namespace std;
    using namespace cml;
    using namespace cml::nn;
    using Function::CrossEntropyLoss;

    auto x = make_tensor<float, 2, 3>({{0.6157993078, 0.4605995417, 0.2293334901},
                                       {0.0736566409, 0.8460972309, 0.7150011659}}, true);
    auto z = make_tensor<float, 2>({1, 1});

    auto loss = CrossEntropyLoss(x, z);
    assert_equals(loss->item(), 0.9676999434641942f);

    loss->backward();

    auto expected_x_gradient = make_tensor<float, 2, 3>({{ 0.1971843602, -0.3311620526,  0.1339776925},
                                                         { 0.0987346902, -0.2862350717,  0.1875003816}});
    assert_equals(x->gradient(), expected_x_gradient);
}

void softmaxTests(){
    softmaxTest();
    softmaxTest2();
    softmaxTest3();

    using namespace std;
    cout << "All Softmax Tests Passed!" << endl << endl;
}

#endif // __CML_TESTS_SOFTMAX_TESTS_H__
