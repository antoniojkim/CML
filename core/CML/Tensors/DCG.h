#ifndef __CML_TENSORS_DCG_H__
#define __CML_TENSORS_DCG_H__

#include <functional>
#include <memory>
#include <utility>
#include <vector>

#include "TensorTemplate.h"

namespace cml {

    template<typename T>
    struct DCG { // Dynamic Compute Graph
        std::vector<tensor<T>> params;
        GradientFunction<T> f;
        bool isLeaf = true;
        tensor<T> gradient;

        DCG(Tensor<T>* t, std::vector<tensor<T>> params, GradientFunction<T> f);

        void accumulateGradient(std::vector<tensor<T>>& gradients);
        
        void backward(std::vector<tensor<T>> x = {make_scalar<T>(1)});

    };

    template <typename T>
    inline std::shared_ptr<DCG<T>> make_graph(Tensor<T>* t,
                                              std::vector<tensor<T>> params,
                                              GradientFunction<T> f) {
        return std::make_shared<DCG<T>>(std::forward<Tensor<T>*>(t),
                                        std::forward<std::vector<tensor<T>>>(params),
                                        std::forward<GradientFunction<T>>(f));
    }

    /***********************************************************************************
    ********************************* Constructors *************************************
    ************************************************************************************/

    template <typename T>
    DCG<T>::DCG(Tensor<T>* t, std::vector<tensor<T>> params, GradientFunction<T> f)
        : params{params},
          f{f},
          isLeaf{params.size() == 0 && f == nullptr},
          gradient{isLeaf ? t->copyLike() : nullptr} {}

    /***********************************************************************************
    *********************************** Methods ****************************************
    ************************************************************************************/


    template<typename T>
    void DCG<T>::accumulateGradient(std::vector<tensor<T>>& gradients){
        for (auto& g : gradients){
            if (gradient->shape() != g->shape()){
                using namespace std;
                cerr << "Dims do not match in accumuateGradient" << endl;
                cerr << "    gradient.shape: " << gradient->shape() << endl;
                cerr << "    g.shape: " << g->shape() << endl;
                throw "Dims do not match in accumuateGradient";
            }
            gradient += g;
        }
    #ifdef DEBUG
        using namespace std;
        cout << "Accumulated Gradient" << endl;
    #endif
    }

    template<typename T>
    void DCG<T>::backward(std::vector<tensor<T>> x){
        if (isLeaf){
            accumulateGradient(x);
        }
        else if (f){
            auto gradients = f(params, x);
            if (params.size() != gradients.size()){
                throw "Number of Gradients does not match number of Parameters";
            }
            for (unsigned int i = 0; i<params.size(); ++i){
                if (params[i]->computeGrad){
                    if (gradients[i] == nullptr){
                        throw "Null Gradient for parameter";
                    }
                    params[i]->graph()->backward({gradients[i]});
                }
            }
        }
    }
}

#endif // __CML_TENSORS_DCG_H__
