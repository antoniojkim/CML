
#include <iostream>
#include <memory>
#include <sstream>
#include <vector>

#include "CML/Tensor.h"
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
    auto paramTest = nn::Sequential<>{
        {"l1", new Linear<>(2, 4)}
    };
    cout << paramTest << endl;
    cout << paramTest["l1"]("weights") << endl;
}

int main(){
    basicSequentialTest();
    simpleParamTest();
}
