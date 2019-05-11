
#include <iostream>
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

int main(){
    Tensor t {2, 3};
    cout << t << endl;
    auto model = nn::Sequential{
        new_module<ReLU>(),
        new_module<nn::Sequential> (
            new_module<ReLU>(),
            new_module<ReLU>()
        ),
        new_module<ReLU>()
    };
    cout << model << endl;

    // auto moduleListModel = nn::ModuleList{
    //     new_module<ReLU>(),
    //     new_module<nn::Sequential> (
    //         new_module<ReLU>(),
    //         new_module<ReLU>()
    //     ),
    //     new_module<ReLU>()
    // };
    // cout << moduleListModel << endl;

    // auto moduleDictModel = nn::ModuleDict{
    //     {"relu1", new_module<ReLU>()},
    //     {"relu2", new_module<ReLU>()},
    //     {"seq1", new_module<nn::Sequential> (
    //         new_module<ReLU>(),
    //         new_module<ReLU>()
    //     )}
    // };
    // cout << moduleDictModel << endl;

    auto paramTest = nn::Sequential {
        new_module<Linear>(2, 4)
    };
    cout << paramTest << endl;
    // auto optimizer = SGD{vector<Parameter>(), 0.1};
}
