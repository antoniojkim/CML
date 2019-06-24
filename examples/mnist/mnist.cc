
#include <iostream>

#include "../../core/CML/nn/Containers.h"
#include "../../core/CML/nn/Linear.h"
#include "../../core/CML/nn/Loss.h"
#include "../../core/CML/nn/Modules.h"
#include "../../core/CML/nn/Nonlinear.h"
#include "readIDX.h"

using namespace std;
using namespace cml;
using namespace cml::nn;


struct MNISTModel: public ModuleList<float> {
    // using ModuleList::Module::addModule;

    MNISTModel(): ModuleList{} {
        addModule<Linear>(728, 64);
        addModule<Sigmoid>();
        addModule<Linear>(64, 64);
        addModule<Sigmoid>();
        addModule<Linear>(64, 10);
        addModule<Softmax>();
    }

};

void train_mnist_model(MNISTModel& model){

}

int main(){

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
    
    auto trainingImages = readMNISTTrainingSetImageFile();
    auto trainingLabels = readMNISTTrainingSetLabelFile();

    auto testImages = readMNISTTestSetImageFile();
    auto testLabels = readMNISTTestSetLabelFile();

    cout << trainingImages.size << endl;
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
