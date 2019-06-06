
#include <iostream>
#include <memory>
#include <sstream>
#include <vector>

#include "CML/Tensor.h"
#include "CML/Functions.h"
#include "CML/nn/Containers.h"
#include "CML/nn/Linear.h"
#include "CML/nn/Nonlinear.h"
#include "CML/optim/Optimizer.h"

using namespace std;
using namespace cml;
using namespace cml::nn;
using namespace cml::optim;

void basicSequentialTest(){
    auto model = nn::Sequential<>{
        new ReLU<>(),
        new nn::Sequential<>{
            new ReLU<>(),
            new ReLU<>()
        },
        new ReLU<>()
    };
    model.addModule("R", new ReLU<>())
         .addModule("T", new ReLU<>())
         .addModule(new ReLU<>());
    cout << model << endl;

    auto relu1 = new ReLU<double>();
    auto doubleModel = nn::Sequential<double>{
        new ReLU<double>(),
        new nn::Sequential<double>{
            new ReLU<double>(),
            new ReLU<double>()
        },
        relu1 // the doubleModel assumes ownership
    };
    cout << doubleModel << endl;
}
void simpleParamTest(){
    auto p = Parameter<double>{2, 3};
    p(0, 0) = 5.5;
    p(1, 1) = 10;
    cout << p << endl;
    auto p2 = p.to<int>();
    cout << p2 << endl;

    auto paramTest = nn::Sequential<>{
        {"l1", new Linear<>(2, 4)}
    };
    cout << paramTest << endl;
    cout << paramTest["l1"]("weights") << endl;
}

void basicTensorTest(){
    using Function::ReLU;
    using Function::Tanh;
    using namespace Function;

    auto t = make_tensor<>(2, 2);
    cout << t << endl;
    t->randomize();
    cout << t << endl;
    t = ReLU(t);
    cout << t << endl;
    cout << endl << "sigmoid:" << endl << Sigmoid(t) << endl;
    cout << endl << "tanh:" << endl << Tanh(t) << endl;
    cout << endl << "mean:" << endl << t->rowwise().mean() << endl;
    cout << endl << "sum:" << endl << t->rowwise().sum() << endl;
    cout << endl << "dot:" << endl << t->data()*t->data() << endl;
    cout << endl << "mul:" << endl << t->array() * t->array() << endl;
}

int main(){
    // basicSequentialTest();
    // simpleParamTest();
    basicTensorTest();
}
