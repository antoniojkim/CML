#ifndef __CML_TESTS_CONVOLUTION_TESTS_H__
#define __CML_TESTS_CONVOLUTION_TESTS_H__

#include "test.h"

void convolutionTest(){
    using namespace cml;
    using namespace cml::nn;
    using Function::Softmax;

    auto x = make_tensor<float, 2, 1>({{1}, {2}}, true);
    
}

void convolutionTests(){
    convolutionTest();

    using namespace std;
    cout << "All Convolution Tests Passed!" << endl << endl;
}

#endif // __CML_TESTS_CONVOLUTION_TESTS_H__
