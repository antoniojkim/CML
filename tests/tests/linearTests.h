#ifndef __CML_TESTS_LINEARTESTS_H__
#define __CML_TESTS_LINEARTESTS_H__

#include "test.h"
#include "../../core/CML/nn/Containers.h"

void linearTest1(){
    using namespace cml;
    using namespace cml::nn;
    using namespace cml::optim;
    using Function::MSELoss;

    auto model = Sequential<float>{
        new Linear<>(3, 2),
        new Sigmoid<>()
    };
    model[0]("weights")->set<3, 2>({{0.284576, -1.16315}, 
                                    {0.270818, 0.0148199}, 
                                    {-0.96044, -0.673953}});
    model[0]("bias")->set<2, 1>({{-0.365125}, {0.889674}});
    
    auto optimizer = optim::SGD<float>(model.parameters(), {{"lr", 0.01}});

    auto x = make_tensor<float, 3, 1>({{1.0}, {2.5}, {7.3}});   
    auto y = model(x);

    assert_equals(y->at(0, 0), 0.00163461f);
    assert_equals(y->at(1, 0),  0.00573006f);

    auto z = make_tensor<float, 2, 1>({{0}, {1}});
    auto loss = MSELoss<float>(y, z);
    // assert_equals(loss->at(0, 0), 0.0723295f);

    assert_equals(loss->item(),  0.494287729f);

    loss->backward();

    
    assert_equals(x->gradient()->at(0, 0),  0.00658952f);
    assert_equals(x->gradient()->at(1, 0),  -8.32261e-05f);
    assert_equals(x->gradient()->at(2, 0),  0.0038151f);
    assert_equals(model[0]("weights")->gradient()->at(0, 0),  2.66758e-06f);
    assert_equals(model[0]("weights")->gradient()->at(0, 1),  -0.00566458f);
    assert_equals(model[0]("weights")->gradient()->at(1, 0),  6.66894e-06f);
    assert_equals(model[0]("weights")->gradient()->at(1, 1),  -0.0141615f);
    assert_equals(model[0]("weights")->gradient()->at(2, 0),  1.94733e-05f);
    assert_equals(model[0]("weights")->gradient()->at(2, 1),  -0.0413514f);
    assert_equals(model[0]("bias")->gradient()->at(0, 0),  2.66758e-06f);
    assert_equals(model[0]("bias")->gradient()->at(1, 0),  -0.00566458f);
    
    optimizer.step();
    
    assert_equals(model[0]("weights")->at(0, 0),  0.2845759690f);
    assert_equals(model[0]("weights")->at(0, 1),  -1.1630933285f);
    assert_equals(model[0]("weights")->at(1, 0),  0.2708179355f);
    assert_equals(model[0]("weights")->at(1, 1),  0.0149615137f);
    assert_equals(model[0]("weights")->at(2, 0),  -0.9604401588f);
    assert_equals(model[0]("weights")->at(2, 1),  -0.6735394597f);
    assert_equals(model[0]("bias")->at(0, 0),  -0.3651250303f);
    assert_equals(model[0]("bias")->at(1, 0),  0.8897306323f);

}


void linearTests(){
    linearTest1();
    std::cout << "All Linear Tests Passed" << std::endl << std::endl;
}

#endif // __CML_TESTS_LINEARTESTS_H__
