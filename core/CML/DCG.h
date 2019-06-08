#ifndef __CML_DCG_H__
#define __CML_DCG_H__

#include <functional>
#include <memory>
#include <utility>

#include "Tensor.h"

namespace cml {

    template<class T>
    struct DCG { // Dynamic Compute Graph
        std::shared_ptr<DCG<T>> parent = nullptr;
        std::function<tensor<T>(tensor<T>)> f  ;

        DCG(std::shared_ptr<DCG<T>>& parent): parent{parent} {}
        
        void backward(tensor<T> x = nullptr){
            if (f){
                auto y = f(x);
                if (parent){
                    parent->backward(y);
                }
            }
        }

    };

    template<typename T, typename... Args>
    inline std::shared_ptr<DCG<T>> make_graph(Args&&... args){
        return std::make_shared<DCG<T>>(std::forward<Args>(args)...);
    }

}

#endif // __CML_DCG_H__
