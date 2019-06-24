
#include <cassert>
#include <iostream>
#include <memory>
#include <sstream>
#include <vector>

#include "../core/CML/Tensor.h"
#include "../core/CML/Functions.h"
#include "../core/CML/nn/Containers.h"
#include "../core/CML/nn/Linear.h"
#include "../core/CML/nn/Nonlinear.h"
#include "../core/CML/nn/Loss.h"

#include "basicGradientsTest.h"
#include "linearTests.h"
#include "softmaxTests.h"

using namespace std;
using namespace cml;
using namespace cml::nn;


int main(){
    try{
        runbasicGradientsTest();
        linearTests();
        softmaxTests();
    } catch (const char* error){
        cerr << error << endl;
        throw;
    }
}
