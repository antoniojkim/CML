
#include <iostream>
#include <vector>

#include "CML/Tensor.h"
#include "CML/nn/Layers.h"
#include "CML/optim/Optimizer.h"

using namespace std;
using namespace cml;
using namespace cml::nn;
using namespace cml::optim;

int main(){
    Tensor t {2, 3};
    cout << t << endl;
    auto model = Sequential{
        new_module<ReLU>()
    };
    auto optimizer = SGD{vector<Parameter>(), 0.1};
}
