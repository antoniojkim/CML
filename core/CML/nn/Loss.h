#ifndef __CML_NN_LOSS_H__
#define __CML_NN_LOSS_H__

#include <map>
#include <memory>
#include <string>

#include "Loss/MSELoss.h"
#include "Loss/CrossEntropyLoss.h"

namespace cml {

    enum Criterions {
        MSELOSS,
        CROSSENTROPYLOSS
    };

    std::map<std::string, Criterions> CriterionMap {
        {"MSELoss", Criterions::MSELOSS},
        {"CrossEntropyLoss", Criterions::CROSSENTROPYLOSS}
    };

    template<typename T>
    std::unique_ptr<nn::Criterion<T>> make_criterion(const std::string& criterion) {
        if (!CriterionMap.count(criterion)){
            throw "Invalid Criterion Provided: " + criterion;
        }

        switch(CriterionMap[criterion]){
            case Criterions::MSELOSS:
                return std::make_unique<nn::MSELoss<T>>();
            case Criterions::CROSSENTROPYLOSS:
                return std::make_unique<nn::CrossEntropyLoss<T>>();
            default:
                throw "Invalid Criterion Provided: " + criterion;
        }
    }

}

#endif // __CML_NN_LOSS_H__
