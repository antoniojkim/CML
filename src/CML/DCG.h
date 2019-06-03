#ifndef __CML_DCG_H__
#define __CML_DCG_H__

#include <functional>

#include "Tensor.h"

namespace cml {

    template<class T>
    struct DCG { // Dynamic Compute Graph
        DCG* parent = nullptr;
        bool root = true;
        std::function<Tensor<T>(Tensor<T>&)> f  ;

        DCG(DCG<T>* parent): parent{parent} {
            if(parent) parent->root = false;
        }
        ~DCG(){
            if (parent) {
                delete parent;
                parent = nullptr;
            }
        }

    };

}

#endif // __CML_DCG_H__
