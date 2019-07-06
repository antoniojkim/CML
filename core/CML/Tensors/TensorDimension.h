#ifndef __CML_TENSORS_TENSORDIMENSION_H__
#define __CML_TENSORS_TENSORDIMENSION_H__

#include <Eigen/Core>
#include "Tensor.h"

namespace cml {

    template<typename T, template<typename> class MatrixType>
    class TensorDimension {};

    template <typename T>
    using DMatrix = Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>;  // Dynamic Matrix

    template<typename T>
    struct TensorDimension<T, DMatrix> {
        DMatrix<T>* m;

        TensorDimension() {}
        TensorDimension(DMatrix<T>* m): m{m} {}
        TensorDimension(DMatrix<T>& m): m{&m} {}

        void setMatrix(DMatrix<T>* m) { this->m = m; }
        void setMatrix(DMatrix<T>& m) { this->m = &m; }

        bool operator==(const TensorDimension<T, DMatrix>& other){
            return m->rows() == other.m->rows() && m->cols() == other.m->cols();
        }
        bool operator!=(const TensorDimension<T, DMatrix>& other){
            return m->rows() != other.m->rows() || m->cols() != other.m->cols();
        }
        bool isScalar(){
            return m->rows() == 1 && m->cols() == 1;
        }

    };

}

#endif // __CML_TENSORS_TENSORDIMENSION_H__
