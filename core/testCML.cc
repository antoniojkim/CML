
#include <cassert>
#include <iostream>
#include <memory>
#include <sstream>
#include <vector>

#include "CML/Tensor.h"
#include "CML/Functions.h"
#include "CML/nn/Containers.h"
#include "CML/nn/Linear.h"
#include "CML/nn/Nonlinear.h"
#include "CML/nn/Loss.h"
// #include "CML/optim/Optimizer.h"

#include "../test/basicGradients/basicGradientsTest.h"

using namespace std;
using namespace cml;
using namespace cml::nn;
// using namespace cml::optim;

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
void basicLinearTest(){
    
    auto model = nn::Sequential<>{
        new Linear<>(2, 4),
        new ReLU<>(),
        new Linear<>(4, 2),
        new ReLU<>()
    };
    cout << model << endl;
    cout << "weights:" << endl << model[0]("weights") << endl << endl;
    
    model.initWeights();
    
    cout << "weights.T:" << endl << model[0]("weights")->transpose() << endl << endl;
    cout << "weights.T:" << endl << model[2]("weights")->transpose() << endl << endl;
    
    // auto criterion = MSELoss<>();
    
    auto input = make_tensor<>(2, 1);
    input->randomize();
    
    cout << "Input:" << endl << input << endl << endl;
    
    auto output = model(input);
    
    cout << "Output:" << endl << output << endl << endl;
    
    // auto expected = make_tensor<>(2, 1);
    // expected->randomize();
    
    // auto loss = criterion(output, expected);
    
    // loss->backward();
    
}

int main(){
    runbasicGradientsTest();
    // try{
        // basicSequentialTest();
        // simpleParamTest();
    //     basicTensorTest();
        // basicLinearTest();
    // } catch (const char* error){
    //     cerr << error << endl;
    //     throw;
    // }
}
