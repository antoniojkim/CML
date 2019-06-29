#ifndef __CML_MODELTRAINER_MODELTRAINER_H__
#define __CML_MODELTRAINER_MODELTRAINER_H__

#include <iostream>
#include <initializer_list>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "../CML/Tensor.h"
#include "../CML/Dtypes.h"
#include "../CML/nn/Loss.h"
#include "../CML/nn/Modules.h"
#include "../CML/optim/Optimizer.h"
#include "../Utils/DataSource.h"

namespace cml {

    template<typename T = float>
    class ModelTrainer {

        nn::Module<T>* model = nullptr;
        DataSource<T>* data = nullptr;
        std::string criterionName;
        std::unique_ptr<nn::Criterion<T>> criterion;
        std::string optimizerName;
        std::unique_ptr<optim::Optimizer<T>> optimizer;

        unsigned int batchSize = 32;
        unsigned int subdivisions = 1;
        unsigned int numAccumulate = 1;

        public:
            ModelTrainer(nn::Module<T>& model, 
                         DataSource<T>& data, 
                         const std::string& criterionName, 
                         const std::string& optimizerName,
                         Kwargs kwargs = {}):
                model{&model}, data{&data}, 
                criterionName{criterionName}, criterion{make_criterion<T>(criterionName)}, 
                optimizerName{optimizerName}, 
                optimizer{make_optimizer<T>(optimizerName, model, std::forward<Kwargs>(kwargs))} {
                
                if (kwargs.count("batchSize")){
                    batchSize = (unsigned int) kwargs["batchSize"];
                }
                if (kwargs.count("subdivisions")){
                    subdivisions = (unsigned int) kwargs["subdivisions"];
                }
                if (kwargs.count("numAccumulate")){
                    numAccumulate = (unsigned int) kwargs["numAccumulate"];
                }
            }

            std::ostream& print(std::ostream& out){
                using namespace std;
                out << "ModelTrainer:" << endl;
                out << "    model:          " << model << endl;
                out << "    data:           " << data << endl;
                out << "    criterion:      " << criterionName << endl;
                out << "    optimizer:      " << optimizerName << endl << endl;
                out << "    batchSize:      " << batchSize << endl;
                out << "    subdivisions:   " << subdivisions << endl;
                out << "    numAccumulate:  " << numAccumulate << endl << endl;
                return out;
            }

    };

    template<typename T>
    std::ostream& operator<<(std::ostream& out, ModelTrainer<T>& trainer){
        return trainer.print(out);
    }



}

#endif // __CML_MODELTRAINER_MODELTRAINER_H__
