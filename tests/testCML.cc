
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
#include "../core/Utils/Exceptions.h"

#include "tests/basicGradientsTest.h"
#include "tests/linearTests.h"
#include "tests/softmaxTests.h"
#include "tests/convolutionTests.h"

using namespace std;
using namespace cml;
using namespace cml::nn;


int main(){
    runbasicGradientsTest();
    linearTests();
    softmaxTests();
    convolutionTests();
}
