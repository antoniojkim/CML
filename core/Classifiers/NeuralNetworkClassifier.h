#ifndef __CML_CLASSIFIERS_NEURALNETWORKCLASSIFIER_H__
#define __CML_CLASSIFIERS_NEURALNETWORKCLASSIFIER_H__

#include <algorithm>
#include <ctime>
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
#include "../Utils/DataReader.h"

namespace cml {
    

    template<typename T>
    class NeuralNetworkClassifier {

        nn::Module<T>* model = nullptr;
        tensor<T> data = nullptr;
        tensor<T> labels = nullptr;
        tensor<T> val = nullptr;
        tensor<T> valLabels= nullptr;
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
        unsigned int valFreq = 1;
        
        bool _verbose = false;

        public:
            NeuralNetworkClassifier(nn::Module<T>& model, 
                                    tensor<T> data, 
                                    tensor<T> labels, 
                                    const std::string& criterionName, 
                                    const std::string& optimizerName,
                                    Kwargs kwargs = {}):
                model{&model}, data{data}, labels{labels}, 
                criterionName{criterionName}, criterion{make_criterion<T>(criterionName)}, 
                optimizerName{optimizerName}, 
                optimizer{make_optimizer<T>(optimizerName, model, std::forward<Kwargs>(kwargs))} {
                
                if (this->data->rows() != this->labels->rows()){
                    throw "Number of data samples does not match number of labels";
                }
                
                std::cout << "kwargs:" << std::endl;
                for (auto kv : kwargs){
                    std::cout << "    " << kv.first << ": " << kv.second << std::endl;
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
            
            void setVal(tensor<T> val, tensor<T> labels){
                this->val = val;
                this->valLabels = labels;
            }
            
            unsigned int& operator[](const std::string& key){
                if (key == "batchSize")         return batchSize;
                if (key == "subdivisions")      return subdivisions;
                if (key == "numAccumulate")     return numAccumulate;
                if (key == "startingEpoch")     return startingEpoch;
                if (key == "startingIteration") return startingIteration;
                if (key == "numEpochs")         return maxEpochs;
                if (key == "maxEpochs")         return maxEpochs;
                if (key == "valFreq")           return valFreq;
                
                throw "Invalid Key:  "+key;
            }
            
            void shuffle() {
                Eigen::VectorXi indices = Eigen::VectorXi::LinSpaced(data->rows(), 0, data->rows());
                std::random_shuffle(indices.data(), indices.data() + data->rows());
                data->randomize(indices);
                labels->randomize(indices);
            }
            
            void train(){
                using namespace std;
                
                
                clock_t start, end;
            
                unsigned int epoch = startingEpoch;
                unsigned int endEpoch = startingEpoch + maxEpochs;
                unsigned int iteration = startingIteration;
                
                unsigned int blockSize = batchSize / subdivisions;
                double totalLoss;
                
                auto block = make_tensor<T>(int(data->cols()), int(blockSize));
                auto label = make_tensor<T>(int(labels->cols()), int(blockSize));
                
                
                for (; epoch < endEpoch; ++epoch){
                    if (_verbose) cout << "Epoch " << epoch << ":" << endl;
                    
                    start = clock();
                    
                    model->grad();
                    totalLoss = 0;
                    optimizer->zeroGrad();
                   
#ifndef DEBUG
                    shuffle();
#endif
                    for (int i = 0; i<data->rows(); i += blockSize){
                        loadData(block, data, i, blockSize);
#ifdef DEBUG
                        using namespace std;
                        cout << "l1.weights:  " << (*model)[0]("weights")->rows() << ", " << (*model)[0]("weights")->cols() << endl;
                        cout << "block:  " << block->rows() << ", " << block->cols() << endl;
#endif
                        auto output = model->forward(block);
                        loadData(label, labels, i, blockSize);
                        
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
                    
                    end = clock();
                    if (_verbose) cout << "Took " << double(end-start)/CLOCKS_PER_SEC << " seconds" << endl;
                    
                    if (epoch%valFreq == 0 && val != nullptr && valLabels != nullptr){
                        using Function::Softmax;
                        model->noGrad();
                        int maxRow, correct = 0, total = 0;
                        for (int i = 0; i<val->rows(); i += blockSize){
                            loadData(block, val, i, blockSize);
                            auto output = Softmax<T>(model->forward(block));
                            loadData(label, valLabels, i, blockSize);
                            
                            for (unsigned int j = 0; j<blockSize; ++j){
                                output->data().col(j).maxCoeff(&maxRow);
                                if (maxRow == label->data(0, j)){
                                    ++correct;
                                }
                                ++total;
                            }
                        }
                        cout << "Validation:    Correct = " << correct << "   Accuracy = " << (double(correct)/total) << endl;
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
                out << "    optimizer:      " << optimizerName << endl;
                optimizer->print(out, "       ") << endl << endl;
                out << "    batchSize:      " << batchSize << endl;
                out << "    subdivisions:   " << subdivisions << endl;
                out << "    numAccumulate:  " << numAccumulate << endl << endl;
                out << "    maxEpochs:      " << maxEpochs << endl;
                return out;
            }
            
        private:            
            void loadData(tensor<T> block, tensor<T> data, const int& i, const unsigned int& blockSize){
                if (int(i+blockSize) < data->rows()){
                    block->data() = data->block(i, blockSize).transpose();
                }
                else {
                    unsigned int finalBlockSize = data->rows() % blockSize;
                    block->block(0, 0, block->rows(), finalBlockSize) = data->block(i, finalBlockSize).transpose();
                    block->block(0, finalBlockSize, block->rows(), block->cols()-finalBlockSize) = DMatrix<T>::Zero(block->rows(), block->cols()-finalBlockSize);
                }
            }

    };

    template<typename T>
    std::ostream& operator<<(std::ostream& out, NeuralNetworkClassifier<T>& classifier){
        return classifier.print(out);
    }



}

#endif // __CML_CLASSIFIERS_NEURALNETWORKCLASSIFIER_H__
