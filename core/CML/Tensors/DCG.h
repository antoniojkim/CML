#ifndef __CML_TENSORS_DCG_H__
#define __CML_TENSORS_DCG_H__

#include <functional>
#include <memory>
#include <utility>
#include <vector>

#include "Tensor.h"

namespace cml {

    template<typename T, template<typename> class MatrixType>
    struct DCG { // Dynamic Compute Graph
        std::vector<tensor<T, MatrixType>> params;
        GradientFunction<T, MatrixType> f;
        bool isLeaf = true;
        tensor<T, MatrixType> gradient;

        DCG(Tensor<T, MatrixType>* t, std::vector<tensor<T, MatrixType>> params, GradientFunction<T, MatrixType> f);

        void accumulateGradient(const std::vector<tensor<T, MatrixType>>& gradients);
        
        void backward(std::vector<tensor<T, MatrixType>> x = {make_tensor<T, MatrixType>({1})});

    };

    template <typename T, template <typename> class MatrixType>
    inline std::shared_ptr<DCG<T, MatrixType>> make_graph(Tensor<T, MatrixType>* t,
                                                          std::vector<tensor<T, MatrixType>> params,
                                                          GradientFunction<T, MatrixType> f) {
        return std::make_shared<DCG<T, MatrixType>>(std::forward<Tensor<T, MatrixType>*>(t),
                                                    std::forward<std::vector<tensor<T, MatrixType>>>(params),
                                                    std::forward<GradientFunction<T, MatrixType>>(f));
    }

    /***********************************************************************************
    ********************************* Constructors *************************************
    ************************************************************************************/

    template <typename T, template <typename> class MatrixType>
    DCG<T, MatrixType>::DCG(Tensor<T, MatrixType>* t, std::vector<tensor<T, MatrixType>> params,
                            GradientFunction<T, MatrixType> f)
        : params{params},
          f{f},
          isLeaf{params.size() == 0 && f == nullptr},
          gradient{isLeaf ? make_tensor<T, MatrixType>(t->rows(), t->cols(), false) : nullptr} {}

    /***********************************************************************************
    *********************************** Methods ****************************************
    ************************************************************************************/


    template<typename T, template <typename> class MatrixType>
    void DCG<T, MatrixType>::accumulateGradient(const std::vector<tensor<T, MatrixType>>& gradients){
        for (auto& g : gradients){
            if (gradient->shape() != g->shape()){
                using namespace std;
                cerr << "Dims do not match in accumuateGradient" << endl;
                cerr << "    gradient.shape: {" << gradient->rows() << ", " << gradient->cols() << "}" << endl;
                cerr << "    g.shape: {" << g->rows() << ", " << g->cols() << "}" << endl;
                throw "Dims do not match in accumuateGradient";
            }
            gradient->data() += g->data();
        }
    #ifdef DEBUG
        using namespace std;
        cout << "Accumulated Gradient" << endl;
    #endif
    }

    template<typename T, template <typename> class MatrixType>
    void DCG<T, MatrixType>::backward(std::vector<tensor<T, MatrixType>> x){
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
