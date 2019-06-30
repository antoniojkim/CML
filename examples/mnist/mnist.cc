
#include <ctime>
#include <iostream>

#include "../../core/CML/nn/Containers.h"
#include "../../core/CML/nn/Linear.h"
#include "../../core/CML/nn/Loss.h"
#include "../../core/CML/nn/Nonlinear.h"
#include "../../core/CML/optim/Optimizer.h"
#include "../../core/Utils/DataSource.h"
#include "../../core/Utils/ModelTrainer.h"

using namespace std;
using namespace cml;
using namespace cml::nn;
using namespace cml::optim;


struct MNISTModel: public Sequential<float> {

    MNISTModel(): Sequential{} {
        addModule<Linear>(784, 64);
        addModule<Sigmoid>();
        addModule<Linear>(64, 64);
        addModule<Sigmoid>();
        addModule<Linear>(64, 10);
    }

};

void train_mnist_model(MNISTModel& model){
    // Get Train Images
    clock_t start = clock();
    cout << "Loading data from:  data/train-images-idx3-ubyte       " << flush;
    
    auto data = DataSource<float>(DataFormat::IDX, "data/train-images-idx3-ubyte");
    data.data /= 255;
    
    clock_t end = clock();
    cout << "Took " << double(end-start)/CLOCKS_PER_SEC << " seconds" << endl;
    
    
    
    // Get Train Labels
    start = clock();
    cout << "Loading labels from:  data/train-labels-idx1-ubyte     " << flush;
    
    auto labels = DataSource<float>(DataFormat::IDX, "data/train-labels-idx1-ubyte");
    labels.data /= 255;
    
    end = clock();
    cout << "Took " << double(end-start)/CLOCKS_PER_SEC << " seconds" << endl;
    
    
    
    auto trainer = ModelTrainer<float>(model, data, labels, "CrossEntropyLoss", "SGD");
    cout << trainer << endl;
    trainer.verbose();
    
    trainer.train();
}

int main(){

    auto model = MNISTModel();
    cout << model << endl;
    
    train_mnist_model(model);

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
