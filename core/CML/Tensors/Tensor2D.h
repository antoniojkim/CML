#ifndef __CML_TENSORS_TENSOR2D_H__
#define __CML_TENSORS_TENSOR2D_H__

#include <Eigen/Core>
#include "Tensor.h"
#include "DCG.h"
#include "../Randomizer.h"

namespace cml {

    template <typename T>
    using DMatrix = Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>;  // Dynamic Matrix

    template <typename T>
    class Tensor<T, DMatrix>: public DMatrix<T> {
        
        public:
            T& item() {
                if (this->isScalar()) return this->data()(0, 0);
                throw "Tensor2D::item:  Cannot get item from non scalar tensor";
            }
        
            void fill(const T& coefficient) {
                this->data() = DMatrix<T>::Constant(this->rows(), this->cols(), coefficient);
            }
            void zero() {
                this->data() = DMatrix<T>::Zero(this->rows(), this->cols());
            }
            void randomize(Randomizer::Function<T> randomizer = Randomizer::Gaussian<T>) {
                throw "Tensor2D::randomize not implemented";
            }
            void randomize(const T& coefficient) {
                throw "Tensor2D::randomize not implemented";
            }
    };

    template <typename T>
    using Tensor2D = Tensor<T, DMatrix>;
    template <typename T>
    using tensor2d = std::shared_ptr<Tensor<T, DMatrix>>;


    /*
        This is the recommended way to construct a matrix
    */
    template <class T, typename... Args>
    inline tensor<T, DMatrix> make_tensor2d(Args&&... args) {
        return std::make_shared<Tensor<T, DMatrix>>(std::forward<Args>(args)...);
    }
    template <class T>
    inline tensor<T, DMatrix> make_tensor2d(tlist<T> data, const bool& computeGrad = false) {
        return std::make_shared<Tensor<T, DMatrix>>(data, computeGrad);
    }
    template <class T>
    inline tensor<T, DMatrix> make_tensor2d(tlist<tlist<T>> data, const bool& computeGrad = false) {
        return std::make_shared<Tensor<T, DMatrix>>(data, computeGrad);
    }
    
}
/*

// template<typename T>
// tensor<T> Tensor<T>::reshape(const int& R, const int& C){
//     return make_tensor<T>(DMatrix<T>(this->data(), R, C));
// }


template<typename T>
void Tensor<T>::randomize(Randomizer::Function<T> randomizer){
    data() = this->unaryExpr(randomizer);
}
template<typename T>
void Tensor<T>::randomize(const T& coefficient){
//     data() = data().unaryExpr([coefficient](T x) -> T { return (T)(gauss(e2) * coefficient); });
}

 */

#endif // __CML_TENSORS_TENSOR2D_H__
