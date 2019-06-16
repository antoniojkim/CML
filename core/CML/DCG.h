#ifndef __CML_DCG_H__
#define __CML_DCG_H__

#include <functional>
#include <memory>
#include <utility>
#include <vector>

#include "Tensor.h"

namespace cml {

    template<class T>
    struct DCG { // Dynamic Compute Graph
        std::vector<tensor<T>> params;
        tensor<T> gradient;
        GradientFunction<T> f;
        bool isLeaf = true;

        DCG(Tensor<T>* t, std::vector<tensor<T>> params, GradientFunction<T> f);

        void accumulateGradient(const std::vector<tensor<T>>& gradients);
        
        void backward(std::vector<tensor<T>> x = {make_tensor<T>({1})});

    };

    template<typename T>
    inline std::shared_ptr<DCG<T>> make_graph(Tensor<T>* t, std::vector<tensor<T>> params, GradientFunction<T> f){
        return std::make_shared<DCG<T>>(std::forward<Tensor<T>*>(t), 
                                        std::forward<std::vector<tensor<T>>>(params), 
                                        std::forward<GradientFunction<T>>(f));
    }

}

#endif // __CML_DCG_H__
