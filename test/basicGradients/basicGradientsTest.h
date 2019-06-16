#include <cassert>
#include <iostream>

#include "../../core/CML/Tensor.h"
#include "../../core/CML/Functions.h"

using namespace std;
using namespace cml;

void runbasicGradientsTest(){
    auto a = make_tensor<>({2}, true);
    auto b = make_tensor<>({3});
    auto c = a*b;
    c->backward();
    
    assert(a->graph()->gradient->data(0, 0) == 3);


    a = make_tensor<>({2}, true);
    b = make_tensor<>({3}, true); 
    c = a*b;
    auto d = make_tensor<>({4}, true);
    auto e = c*d;
    e->backward();

    assert(d->graph()->gradient->data(0, 0) == 6);
    assert(b->graph()->gradient->data(0, 0) == 8);
    assert(a->graph()->gradient->data(0, 0) == 12);


    using Function::ReLU;

    a = make_tensor<>({{-2}, {3}}, true);
    b = make_tensor<>({{5, 8}}, true);
    c = b*a;
    d = ReLU(c);

    d->backward();

    assert(b->graph()->gradient->data(0, 0) == -2);
    assert(b->graph()->gradient->data(0, 1) == 3);
    assert(a->graph()->gradient->data(0, 0) == 5);
    assert(a->graph()->gradient->data(1, 0) == 8);

    cout << "All Basic Gradient Tests Passed!" << endl;
}