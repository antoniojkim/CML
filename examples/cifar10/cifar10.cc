
#include <Eigen/Core>
#include <iostream>

#include "CML/core/nn/Containers.h"
#include "CML/core/nn/Linear.h"
#include "CML/core/nn/Loss.h"
#include "CML/core/nn/Nonlinear.h"
#include "CML/core/optim/Optimizer.h"
#include "CML/core/Tensor.h"
#include "CML/utils/DataReader.h"
#include "CML/utils/Timer.h"

using namespace std;
using namespace cml;
using namespace cml::nn;
using namespace cml::optim;

// typedef double cifar10Type;

// struct Cifar10Model: public Sequential<cifar10Type> {

//     Cifar10Model(): Sequential{} {
//         // addModule<Sigmoid>();
//         // addModule<Linear>(64, 10);
//     }

// };

// void train_cifar10_model(Cifar10Model& model){
//     auto C10BatchVectorReader = DataReader<cifar10Type>(DataFormat::C10);

//     // Get Train Data
//     tensor<cifar10Type> data;

//     TIMEIT {
//         cout << "Loading data from:  data/cifar-10-batches-bin/data_batch_*.bin       " << flush;

//         data = C10BatchVectorReader.load("data/cifar-10-batches-bin/data_batch_1.bin");
// #ifndef TEST
//         data = data->concat(C10BatchVectorReader.load("data/cifar-10-batches-bin/data_batch_2.bin"));
//         data = data->concat(C10BatchVectorReader.load("data/cifar-10-batches-bin/data_batch_3.bin"));
//         data = data->concat(C10BatchVectorReader.load("data/cifar-10-batches-bin/data_batch_4.bin"));
//         data = data->concat(C10BatchVectorReader.load("data/cifar-10-batches-bin/data_batch_5.bin"));
// #endif
//         data /= 255;
//     }


//     // Get Test Data
//     tensor<cifar10Type> test;

//     TIMEIT {
//         test = C10BatchVectorReader.load("data/cifar-10-batches-bin/data_batch_1.bin");
//         test /= 255;
//     }


//     auto classifier = NeuralNetworkClassifier<cifar10Type>(model, data, labels, "CrossEntropyLoss", "SGD", {{"lr", 3.0}});
//     classifier.setVal(valImages, valImageLabels);
//     classifier["numEpochs"] = 30;
//     classifier.verbose();
//     cout << classifier << endl;

//     classifier.train();
// }

int main(){

    cout  << "Num Threads:  " << Eigen::nbThreads() << endl;

    // auto model = MNISTModel();
    // cout << model << endl;

    // train_mnist_model(model);

    // auto testInput = make_tensor<>(728);
    // testInput->randomize();

    // auto y = model(testInput);
    // cout << y << endl;

    // auto testExpected = make_tensor<>(10);
    // testExpected->randomize();

    // auto loss = criterion(y, testExpected);
    // loss->backward();

    // auto trainingImages = readMNISTTrainingSetImageFile();
    // auto trainingLabels = readMNISTTrainingSetLabelFile();

    // auto testImages = readMNISTTestSetImageFile();
    // auto testLabels = readMNISTTestSetLabelFile();

    // cout << trainingImages.size << endl;
}
/*
float f1 = -187.33667, f2 = 0.0;
std::ofstream out("test.bin",std::ios_base::binary);
if(out.good()){
    std::cout << "Writing floating point number: " << std::fixed << f1 << std::endl;
    out.write((char *)&f1,sizeof(float));
    out.close();
}
std::ifstream in("test.bin",std::ios_base::binary);
if(in.good()){
    in.read((char *)&f2,sizeof(float));
    std::cout << "Reading floating point number: " << std::fixed << f2 << std::endl;
}
*/
