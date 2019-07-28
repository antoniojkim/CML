#ifndef __CML_TENSORS_BATCHVECTOR_H__
#define __CML_TENSORS_BATCHVECTOR_H__
#include <Eigen/Core>
#include <algorithm>

#include "TensorTemplate.h"
#include "DCG.h"
#include "../Randomizer.h"

namespace cml {
    template <typename T> class BatchVector;

    template <typename T>
    class BatchVector: public Tensor<T> {
        
        DMatrix<T> m;
        
        public:
            BatchVector(const int& N, const int& R):
                Tensor<T>(false, {N, R}, TensorType::MATRIX), m{N, R} {}
            BatchVector(std::vector<int>& dims)
                : Tensor<T>(false, dims, TensorType::MATRIX),
                  m{TensorDimension::numBatches(dims), TensorDimension::size(dims)} {}

            inline DMatrix<T>& data() override { return m; }
        
            T& at(const int& N, const int& R) override { return m(N, R); }

            DBlock<T> block(const int& index, const int& batchSize) override {
                return m.block(index, 0, std::min(batchSize, int(m.rows()-index)), m.cols());
            }

            inline void randomize(const unsigned int& seed) override {
                srand(seed);
                randomize(Randomizer::eigenMatrixRandomizer(m.rows()));
            }
            inline void randomize(const Eigen::VectorXi& indices) override {
                m = indices.asPermutation() * m;
            }

            inline int rows() override { return m.rows(); }
            inline int cols() override { return m.cols(); }
    };


    /*
        This is the recommended way to construct a matrix tensor
    */
    template <typename T = float, typename... Args>
    inline tensor<T> make_batch_vector(Args&&... args) {
        return std::make_shared<BatchVector<T>>(std::forward<Args>(args)...);
    }
    
}

#endif // __CML_TENSORS_BATCHVECTOR_H__
