
#include <iostream>

#include "readIDX.h"

using namespace std;

int main(){
    auto trainingImages = readMNISTTrainingSetImageFile();
    auto trainingLabels = readMNISTTrainingSetLabelFile();

    auto testImages = readMNISTTestSetImageFile();
    auto testLabels = readMNISTTestSetLabelFile();

    cout << trainingImages.size << endl;
}
