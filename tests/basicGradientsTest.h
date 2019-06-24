#include <cassert>
#include <iostream>

#include "test.h"
#include "../core/CML/Tensor.h"
#include "../core/CML/Functions.h"


void basicGradientsTest1(){
    using namespace cml;

    auto a = make_tensor<>({2}, true);
    auto b = make_tensor<>({3});
    auto c = a*b;
    c->backward();
    
    assert(a->gradient()->data(0, 0) == 3);


    a = make_tensor<>({2}, true);
    b = make_tensor<>({3}, true); 
    c = a*b;
    auto d = make_tensor<>({4}, true);
    auto e = c*d;
    e->backward();

    assert(d->gradient()->data(0, 0) == 6);
    assert(b->gradient()->data(0, 0) == 8);
    assert(a->gradient()->data(0, 0) == 12);


    using Function::ReLU;

    a = make_tensor<>({{-2}, {3}}, true);
    b = make_tensor<>({{5, 8}}, true);
    c = b*a;
    d = ReLU(c);

    d->backward();

    assert(b->gradient()->data(0, 0) == -2);
    assert(b->gradient()->data(0, 1) == 3);
    assert(a->gradient()->data(0, 0) == 5);
    assert(a->gradient()->data(1, 0) == 8);

}

void runbasicGradientsTest(){
    basicGradientsTest1();
    using namespace std;
    cout << "All Basic Gradient Tests Passed!" << endl << endl;
}