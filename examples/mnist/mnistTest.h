#ifndef __CML_TESTS_MNIST_MNISTTEST_H__
#define __CML_TESTS_MNIST_MNISTTEST_H__

#include "../../core/CML/nn/Containers.h"
#include "../../core/CML/nn/Linear.h"
#include "../../core/CML/nn/Loss.h"
#include "../../core/CML/nn/Modules.h"
#include "../../core/CML/nn/Nonlinear.h"
#include "../test.h"
#include "readIDX.h"

struct MNISTModel: public cml::nn::ModuleList<float> {
    using ModuleList::Module::addModule;

    MNISTModel(): ModuleList{} {
        addModule<cml::nn::Linear>(728, 64);
        addModule<cml::nn::Sigmoid>();
        addModule<cml::nn::Linear>(64, 64);
        addModule<cml::nn::Sigmoid>();
        addModule<cml::nn::Linear>(64, 10);
        addModule<cml::nn::Softmax>();
    }

};

void train_mnist_model(MNISTModel& model){

}


void mnistTest(){
    using namespace std;
    using namespace cml;
    using Function::Softmax;

    auto model = MNISTModel();
    model.initWeights();
    model.grad();
    cout << model << endl;
    
    auto criterion = nn::MSELoss<float>();


    auto testInput = make_tensor<>(728);
    testInput->randomize();

    auto y = model(testInput);
    cout << y << endl;

    auto testExpected = make_tensor<>(10);
    testExpected->randomize();

    auto loss = criterion(y, testExpected);
    loss->backward();
}

#endif // __CML_TESTS_MNIST_MNISTTEST_H__
