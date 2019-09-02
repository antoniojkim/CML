#include <cassert>
#include <iostream>

#include "test.h"


void basicGradientsTest1(){
    using namespace cml;
    using namespace std;

    auto a = make_scalar<float>(2.0f, true);
    auto b = make_scalar<float>(3.0f);
    auto c = a*b;
    c->backward();

    assert_equals(a->gradient()->item(), 3);


    a = make_scalar<float>(2.0f, true);
    b = make_scalar<float>(3.0f, true);
    c = a*b;
    auto d = make_scalar<float>(4.0f, true);
    auto e = c*d;
    e->backward();

    assert_equals(d->gradient()->item(), 6);
    assert_equals(b->gradient()->item(), 8);
    assert_equals(a->gradient()->item(), 12);


    using Function::ReLU;

    a = make_tensor<float, 2, 1>({{-2.0f}, {3.0f}}, true);
    b = make_tensor<float, 1, 2>({{5.0f, 8.0f}}, true);
    c = b->matmul(a);
    d = ReLU(c);

    d->backward();

    assert_equals(b->gradient()->at(0, 0), -2);
    assert_equals(b->gradient()->at(0, 1), 3);
    assert_equals(a->gradient()->at(0, 0), 5);
    assert_equals(a->gradient()->at(1, 0), 8);

}

void runbasicGradientsTest(){
    basicGradientsTest1();
    using namespace std;
    cout << "All Basic Gradient Tests Passed!" << endl << endl;
}