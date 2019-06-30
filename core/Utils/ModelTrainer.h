#ifndef __CML_MODELTRAINER_MODELTRAINER_H__
#define __CML_MODELTRAINER_MODELTRAINER_H__

#include <algorithm>
#include <iostream>
#include <initializer_list>
#include <memory>
#include <string>
#include <utility>
#include <vector>
#include <Eigen/Core>

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
        DataSource<T>* labels = nullptr;
        std::string criterionName;
        std::unique_ptr<nn::Criterion<T>> criterion;
        std::string optimizerName;
        std::unique_ptr<optim::Optimizer<T>> optimizer;

        unsigned int batchSize = 32;
        unsigned int subdivisions = 1;
        unsigned int numAccumulate = 1;
        
        unsigned int startingEpoch = 0;
        unsigned int startingIteration = 0;
        
        unsigned int maxEpochs = 1;
        
        bool _verbose = false;

        public:
            ModelTrainer(nn::Module<T>& model, 
                         DataSource<T>& data, 
                         DataSource<T>& labels, 
                         const std::string& criterionName, 
                         const std::string& optimizerName,
                         Kwargs kwargs = {}):
                model{&model}, data{&data}, labels{&labels}, 
                criterionName{criterionName}, criterion{make_criterion<T>(criterionName)}, 
                optimizerName{optimizerName}, 
                optimizer{make_optimizer<T>(optimizerName, model, std::forward<Kwargs>(kwargs))} {
                
                if (this->data->data.rows() != this->labels->data.rows()){
                    throw "Number of data samples does not match number of labels";
                }
                
                for (auto kv : kwargs){
                    std::cout << kv.first << ": " << kv.second << std::endl;
                }
                
                if (kwargs.count("batchSize")){
                    batchSize = (unsigned int) kwargs["batchSize"];
                }
                if (kwargs.count("subdivisions")){
                    subdivisions = (unsigned int) kwargs["subdivisions"];
                }
                if (kwargs.count("numAccumulate")){
                    numAccumulate = (unsigned int) kwargs["numAccumulate"];
                }
                if (kwargs.count("startingEpoch")){
                    startingEpoch = (unsigned int) kwargs["startingEpoch"];
                }
                if (kwargs.count("startingIteration")){
                    startingIteration = (unsigned int) kwargs["startingIteration"];
                }
                
                if (batchSize % subdivisions != 0){
                    throw "Number of subdivisions do not evenly divide the batchSize";
                }
            }
            
            void shuffle() {
                Eigen::VectorXi indices = Eigen::VectorXi::LinSpaced(data->data.rows(), 0, data->data.rows());
                std::random_shuffle(indices.data(), indices.data() + data->data.rows());
                data->data = indices.asPermutation() * data->data;
                labels->data = indices.asPermutation() * labels->data;
            }
            
            void train(){
                using namespace std;
            
                unsigned int epoch = startingEpoch;
                unsigned int endEpoch = startingEpoch + maxEpochs;
                unsigned int iteration = startingIteration;
                
                unsigned int blockSize = batchSize / subdivisions;
                unsigned int finalBlockSize = data->data.rows() % blockSize;
                double totalLoss;
                
                auto block = make_tensor<T>(data->data.cols(), blockSize);
                auto label = make_tensor<T>(labels->data.cols(), blockSize);
                
                
                for (; epoch < endEpoch; ++epoch){
                    if (_verbose) cout << "Epoch " << epoch << ":" << endl;
                    
                    totalLoss = 0;
                    optimizer->zeroGrad();
                   
                    shuffle();
                    for (unsigned int i = 0; i<data->data.rows(); i += blockSize){
                        if (i+blockSize < data->data.rows()){
                            block->data() = data->data.block(i, 0, blockSize, data->data.cols()).transpose();
                        }
                        else {
                            block->block(0, 0, block->rows(), finalBlockSize) = data->data.block(i, 0, finalBlockSize, data->data.cols()).transpose();
                            block->block(0, finalBlockSize, block->rows(), block->cols()-finalBlockSize) = DMatrix<T>::Zero(block->rows(), block->cols()-finalBlockSize);
                        }
                        
                        auto output = model->forward(block);
                        if (i+blockSize < data->data.rows()){
                            label->data() = labels->data.block(i, 0, blockSize, labels->data.cols()).transpose();
                        }
                        else {
                            label->block(0, 0, label->rows(), finalBlockSize) = labels->data.block(i, 0, finalBlockSize, labels->data.cols()).transpose();
                            label->block(0, finalBlockSize, label->rows(), label->cols()-finalBlockSize) = DMatrix<T>::Zero(label->rows(), label->cols()-finalBlockSize);
                        }
                        
                        auto loss = criterion->forward(output, label);
                        totalLoss += loss->item();
                        loss->backward();
                        
                        if ((i+blockSize)%batchSize == 0 && ((i+blockSize)/batchSize)%numAccumulate == 0){
                            optimizer->step();
                            optimizer->zeroGrad();
                            
                            if (_verbose) cout << "    " << iteration << ":    Current Loss = " << (totalLoss/(subdivisions*numAccumulate)) << endl;
                            totalLoss = 0;
                        }
                        
                        ++iteration;
                    }
                }
            }
            
            void verbose(const bool& verbose = true){
                _verbose = verbose;
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
                out << "    maxEpochs:      " << maxEpochs << endl;
                return out;
            }

    };

    template<typename T>
    std::ostream& operator<<(std::ostream& out, ModelTrainer<T>& trainer){
        return trainer.print(out);
    }



}

#endif // __CML_MODELTRAINER_MODELTRAINER_H__
