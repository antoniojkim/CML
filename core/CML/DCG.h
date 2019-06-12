#ifndef __CML_DCG_H__
#define __CML_DCG_H__

#include <functional>
#include <memory>
#include <utility>

#include "Tensor.h"

namespace cml {

    template<class T>
    struct DCG { // Dynamic Compute Graph
        bool isLeaf = true;
        tensor<T> gradient;
        std::function<void(tensor<T>)> f;

        DCG(Tensor<T>* t, std::function<void(tensor<T>)> f): 
            gradient{make_tensor<T>(t->rows(), t->cols(), false)}, f{f} {}


        void accumulateGradient(const T& scalar){
            gradient->data() += DMatrix<T>::Constant(gradient->rows(), gradient->cols(), scalar);
        }
        void accumulateGradient(tensor<T> t){
            if (gradient->rows() != t->rows() || gradient->cols() != t->cols()){
                throw "Dims do not match in accumuateGradient";
            }
            gradient->data() += t->data();
        }
        
        void backward(tensor<T> x = make_tensor<T>({1})){
            if (f){
//                 if (x) std::cout << x << std::endl;
                f(x);
                // f = nullptr;
            }
        }

    };

    template<typename T, typename... Args>
    inline std::shared_ptr<DCG<T>> make_graph(Args&&... args){
        return std::make_shared<DCG<T>>(std::forward<Args>(args)...);
    }

}

#endif // __CML_DCG_H__
