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
#include "../Utils/VectorUtils.h"

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

        size_t batchSize = 32;
        size_t subdivisions = 1;
        size_t numAccumulate = 1;

        size_t startingEpoch = 0;
        size_t startingIteration = 0;

        size_t maxEpochs = 1;
        size_t valFreq = 1;

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
                    batchSize = (size_t) kwargs["batchSize"];
                }
                if (kwargs.count("subdivisions")){
                    subdivisions = (size_t) kwargs["subdivisions"];
                }
                if (kwargs.count("numAccumulate")){
                    numAccumulate = (size_t) kwargs["numAccumulate"];
                }
                if (kwargs.count("startingEpoch")){
                    startingEpoch = (size_t) kwargs["startingEpoch"];
                }
                if (kwargs.count("startingIteration")){
                    startingIteration = (size_t) kwargs["startingIteration"];
                }

                if (batchSize % subdivisions != 0){
                    throw "Number of subdivisions do not evenly divide the batchSize";
                }
            }

            void setVal(tensor<T> val, tensor<T> labels){
                this->val = val;
                this->valLabels = labels;
            }

            size_t& operator[](const std::string& key){
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
                
                data->matrix() = indices.asPermutation() * data->matrix();
                labels->matrix() = indices.asPermutation() * labels->matrix();
            }

            void train(){
                using namespace std;


                clock_t start, end;

                size_t epoch = startingEpoch;
                size_t endEpoch = startingEpoch + maxEpochs;
                size_t iteration = startingIteration;

                size_t blockSize = batchSize / subdivisions;
                double totalLoss;

                auto block = make_tensor<T>(std::vector<size_t>({size_t(blockSize), size_t(data->cols())}));
                auto label = make_tensor<T>(std::vector<size_t>({size_t(blockSize)}));

#ifdef DEBUG    
                cout << "data.shape:    "; cml::print(cout, data->shape()) << endl;
                cout << "labels.shape:  "; cml::print(cout, labels->shape()) << endl;
                cout << "block.shape:   "; cml::print(cout, block->shape()) << endl;
                cout << "label.shape:   "; cml::print(cout, label->shape()) << endl;
#endif

                for (; epoch < endEpoch; ++epoch){
                    if (_verbose) cout << "Epoch " << epoch << ":" << endl;

                    start = clock();

                    model->grad();
                    totalLoss = 0;
                    optimizer->zeroGrad();

#ifndef DEBUG
                    shuffle();
#endif
                    for (size_t i = 0; i < data->rows(); i += blockSize){
                        loadData(block, data, i, blockSize);
                        auto output = model->forward(block);
                        loadData(label, labels, i, blockSize, false);

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
                        for (size_t i = 0; i < val->rows(); i += blockSize){
                            loadData(block, val, i, blockSize);
                            auto output = Softmax<T>(model->forward(block));
                            loadData(label, valLabels, i, blockSize, false);

                            for (size_t j = 0; j<blockSize; ++j){
                                output->matrix().row(j).maxCoeff(&maxRow);
                                if (maxRow == label->at(j)){
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
                out << "    data:           " << data.get() << endl;
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
            void loadData(tensor<T> block, tensor<T> data, const int& i, const size_t& blockSize, const bool& transpose = true){
                if (size_t(i+blockSize) < data->rows()){
// #ifdef DEBUG
//                     auto lhs = block->matrix();
//                     auto rhs = data->block(i, blockSize).transpose();
//                     using namespace std;
//                     cout << "lhs:  [" << lhs.rows() << ", " << lhs.cols() << "]" << endl;
//                     cout << "rhs:  [" << rhs.rows() << ", " << rhs.cols() << "]" << endl;
// #endif           
                    block->matrix() = data->block(i, blockSize);
                }
                else {
                    size_t finalBlockSize = data->cols() % blockSize;
// #ifdef TEST
//                     using namespace std;
//                     cout << "block.shape = [" << block->rows() << ", " << block->cols() << "]" << endl;
//                     cout << "finalBlockSize = " << finalBlockSize << endl;
//                     auto lhs = block->block(finalBlockSize, 0, block->rows()-finalBlockSize, block->cols());
//                     auto rhs = DMatrix<T>::Zero(block->rows()-finalBlockSize, block->cols());
//                     cout << "lhs:  [" << lhs.rows() << ", " << lhs.cols() << "]" << endl;
//                     cout << "rhs:  [" << rhs.rows() << ", " << rhs.cols() << "]" << endl;
// #endif           
                    block->block(0, 0, finalBlockSize, block->cols()) = data->block(i, finalBlockSize);
                    block->block(finalBlockSize, 0, block->rows()-finalBlockSize, block->cols()) = DMatrix<T>::Zero(block->rows()-finalBlockSize, block->cols());
                }
            }

    };

    template<typename T>
    std::ostream& operator<<(std::ostream& out, NeuralNetworkClassifier<T>& classifier){
        return classifier.print(out);
    }



}

#endif // __CML_CLASSIFIERS_NEURALNETWORKCLASSIFIER_H__
