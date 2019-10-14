#ifndef __CML_TENSORS_DCG_H__
#define __CML_TENSORS_DCG_H__

#include <functional>
#include <memory>
#include <utility>
#include <vector>

#include "../../Utils/VectorUtils.h"

namespace cml {

    template<typename T>
    struct DCG { // Dynamic Compute Graph
        std::vector<tensor<T>> params;
        GradientFunction<T> f;
        bool isLeaf = true;
        tensor<T> gradient;

        DCG(tensor<T> t, const std::vector<cml::tensor<T>>& params, GradientFunction<T> f);

        void accumulateGradient(std::vector<tensor<T>>& gradients);

        void backward(std::vector<tensor<T>> x = {make_scalar<T>(1)});

    };

    template <typename T>
    inline std::shared_ptr<DCG<T>> make_graph(tensor<T> t,
                                              const std::vector<tensor<T>>& params,
                                              GradientFunction<T> f) {
        return std::make_shared<DCG<T>>(t, params, f);
    }

    /***********************************************************************************
    ********************************* Constructors *************************************
    ************************************************************************************/

    template <typename T>
    DCG<T>::DCG(tensor<T> t, const std::vector<cml::tensor<T>>& params, GradientFunction<T> f)
        : params{params},
          f{f},
          isLeaf{params.size() == 0 && f == nullptr},
          gradient{isLeaf ? t->constant(0) : nullptr}
    {
#ifdef DEBUG
        if (isLeaf && t->shape() != gradient->shape()){
            throw CMLException("Gradient Shape does not match tensor: ", t->shape(), "!=", gradient->shape());
        }
#endif       
    }

    /***********************************************************************************
    *********************************** Methods ****************************************
    ************************************************************************************/


    template<typename T>
    void DCG<T>::accumulateGradient(std::vector<tensor<T>>& gradients){
        for (auto& g : gradients){
            if (gradient->shape() != g->shape() &&
                !(g->numDims() == 2 && gradient->rows() == g->rows() && gradient->cols() == g->cols())){
                throw CMLException("Dims do not match in accumulateGradient\n",
                                   "    gradient.shape: ", gradient->shape(), "\n",
                                   "    g.shape: ", g->shape(), "\n");
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
                throw CMLException("Number of Gradients does not match number of Parameters");
            }
            for (size_t i = 0; i<params.size(); ++i){
                if (params[i]->computeGrad){
                    if (gradients[i] == nullptr){
                        throw CMLException("Null Gradient for parameter");
                    }
                    params[i]->graph()->backward({gradients[i]});
                }
            }
        }
    }




    /***********************************************************************************
    ****************************** Tensor DCG Methods **********************************
    ************************************************************************************/

    template <typename T>
    inline void Tensor<T>::initGraph(const std::vector<cml::tensor<T>>& params, GradientFunction<T> f){
        if (!dcg) {
            dcg = std::make_unique<DCG<T>>(this->shared_from_this(), params, f);
        } else {
            throw CMLException("Called initGraph when graph already exists");
        }
    }

    template <typename T>
    std::unique_ptr<DCG<T>>& Tensor<T>::graph(){
        if (!dcg) {
            if (!computeGrad) throw CMLException("Getting graph of tensor with computeGrad == false");
            initGraph();
        }
        return dcg;
    }

    template <typename T>
    tensor<T> Tensor<T>::gradient(){ return graph()->gradient; }

    template <typename T>
    void Tensor<T>::backward(){
        if (!isScalar()) throw CMLException("backward can only be called on a scalar tensor. Dims: ", dims);
#ifdef DEBUG
        std::cout << "Calling backward on a scalar tensor" << std::endl;
#endif
        graph()->backward();
    }

}

#endif // __CML_TENSORS_DCG_H__
