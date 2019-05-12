
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
    auto model = nn::Sequential{
        new_module<ReLU>(),
        new_module<nn::Sequential> (
            new_module<ReLU>(),
            new_module<ReLU>()
        ),
        new_module<ReLU>()
    };
    cout << model << endl;
}
void simpleParamTest(){
    auto paramTest = nn::Sequential {
        {"l1", new_module<Linear>(2, 4)}
    };
    cout << paramTest << endl;
    cout << paramTest["l1"]("weights") << endl;
}

int main(){
    Tensor t {2, 3};
    cout << t << endl;
    basicSequentialTest();
    simpleParamTest();
}
