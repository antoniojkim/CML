#ifndef __CML_DCG_H__
#define __CML_DCG_H__

#include <functional>

#include "Tensor.h"

namespace cml {

    template<class T>
    struct DCG { // Dynamic Compute Graph
        DCG* parent = nullptr;
        std::function<Tensor<T>(Tensor<T>&)> f;

        DCG(DCG<T>* parent): parent{parent} {}
        ~DCG(){ if (parent) delete parent; }
    };

}

#endif // __CML_DCG_H__
