
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
