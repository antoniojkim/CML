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
    model[0]("weights")->set<2, 3>({{ 0.284576,  0.270818, -0.960440},
                                    {-1.163150,  0.014820, -0.673953}});                                    
    model[0]("bias")->set<2>({-0.365125,  0.889674});

    auto optimizer = optim::SGD<float>(model.parameters(), {{"lr", 0.01}});

    auto x = make_tensor<float, 1, 3>({{1.0, 2.5, 7.3}}, true);
    auto y = model(x);
    
    auto expected = make_tensor<float, 1, 2>({{0.00163461f, 0.00573006f}});
    assert_equals(y, expected);

    auto z = make_tensor<float, 1, 2>({{0, 1}});
    auto loss = MSELoss(y, z);
    // assert_equals(loss->at(0, 0), 0.0723295f);

    assert_equals(loss->item(),  0.494287729f);

    loss->backward();

    auto expected_x_gradient = make_tensor<float, 1, 3>({{0.00658952f, -8.32261e-05f, 0.0038151f}});
    assert_equals(x->gradient(), expected_x_gradient);

    auto expected_weights_gradient = make_tensor<float, 2, 3>({{ 2.667576e-06f,  6.668939e-06f,  1.947330e-05f},
                                                               {-5.664581e-03f, -1.416145e-02f, -4.135144e-02f}});
    assert_equals(model[0]("weights")->gradient(), expected_weights_gradient);

    auto expected_bias_gradient = make_tensor<float, 2>({ 2.667576e-06, -5.664581e-03});
    assert_equals(model[0]("bias")->gradient(), expected_bias_gradient);

    optimizer.step();

    auto expected_new_weights = make_tensor<float, 2, 3>({{ 0.2845759690f,  0.2708179355f, -0.9604401588f},
                                                          {-1.1630933285f,  0.0149616143f, -0.6735394597f}});
    assert_equals(model[0]("weights"), expected_new_weights);

    auto expected_new_bias = make_tensor<float, 2>({-0.3651250005f,  0.8897309899f});
    assert_equals(model[0]("bias"), expected_new_bias);

}


void linearTests(){
    linearTest1();
    std::cout << "All Linear Tests Passed" << std::endl << std::endl;
}

#endif // __CML_TESTS_LINEARTESTS_H__
