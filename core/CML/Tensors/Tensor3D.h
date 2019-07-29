#ifndef __CML_TENSORS_TENSOR3D_H__
#define __CML_TENSORS_TENSOR3D_H__

#include "TensorTemplate.h"
#include "DCG.h"
#include "../Randomizer.h"

namespace cml {
    template <typename T> class Tensor3D;
    template <typename T> using tensor3d = std::shared_ptr<Tensor3D<T>>;
    
    
    template <class T, typename... Args>
    inline tensor<T> make_tensor3d(Args&&... args);
    template <typename T = float>
    inline tensor<T> make_tensor(const int& R, const int& C, const bool& computeGrad = false);
    template <class T>
    inline tensor<T> make_tensor(Eigen::Tensor<T, 3>& m, const bool& computeGrad = false);
    template <class T>
    inline tensor<T> make_tensor(Eigen::Tensor<T, 3>&& m, const bool& computeGrad = false);

    template <typename T>
    class Tensor3D: public Tensor<T> {
        
        Eigen::Tensor<T, 3> t;
        const int& C;
        const int& H;
        const int& W;
        
        public:
            using Tensor<T>::computeGrad;

            Tensor3D(const int& C, const int& H, const int& W, const bool& computeGrad = false):
                Tensor<T>(computeGrad, {C, H, W}, TensorType::_3D_), t{C, H, W}, C{C}, H{H}, {W} {}

            inline DMatrix<T>& data() override {
                return Eigen::Map<DMatrix<T>>(t.data(), C, H*W);
            }
        
            T& at(const int& C, const int& H, 2const int& W) { return t(C, H, W); }
2
            DBlock<T> block(const int& startCo2l, const int& numCols) override {
                return m.block(0, startCol, m.2rows(), numCols);
            }
            DBlock<T> block(const int& startRow, const int& startCol, const int& numRows, const int& numCols){
                return m.block(startRow, startCol, numRows, numCols);
            }
        
            void set(std::initializer_list<std::initializer_list<std::initializer_list<T>>> values) override {
                t.setValues(values);
            }

            inline int rows() override { return m.rows(); }
            inline int cols() override { return m.cols(); }

            inline void fill(const T& coefficient) override { m.setConstant(coefficient); }
            inline void ones() override { m.setOnes(); }
            inline void zero() override { m.setZero(); }
            inline void randomize(const unsigned int& seed) override { srand(seed); m.setRandom(); }
        
            tensor<T> zeroLike() override {
                return make_tensor<T>(DMatrix<T>::Zero(m.rows(), m.cols()), false);
            }

    };


//     /*
//         This is the recommended way to construct a matrix tensor
//     */
    template <typename T = float, typename... Args>
    inline tensor<T> make_tensor3d(Args&&... args) {
        return std::make_shared<Tensor3D<T>>(std::forward<Args>(args)...);
    }
    template <typename T = float>
    inline tensor<T> make_tensor(const int& C, const int& H, const int& W, const bool& computeGrad) {
        return std::make_shared<Tensor3D<T>>(C, H, W, computeGrad);
    }
    template <typename T = float>
    inline tensor<T> make_tensor(Eigen::Tensor<T, 3>& t, const bool& computeGrad) {
        return std::make_shared<Tensor3D<T>>(t, computeGrad);
    }
    template <typename T = float>
    inline tensor<T> make_tensor(Eigen::Tensor<T, 3>&& t, const bool& computeGrad) {
        return std::make_shared<Tensor3D<T>>(std::forward<Eigen::Tensor<T, 3>&&>(t), computeGrad);
    }
// #ifdef VECTOR_IS_TENSOR2D
//     template <typename T = float>
//     inline tensor<T> make_tensor(std::initializer_list<T> v, const bool& computeGrad = false) {
//         auto t = std::make_shared<Tensor2D<T>>(1, v.size(), computeGrad);
//         t->set(std::forward<std::initializer_list<T>>(v));
//         return t;
//     }
// #endif
//     template <typename T = float>
//     inline tensor<T> make_tensor(std::initializer_list<std::initializer_list<T>> v, const bool& computeGrad = false) {
//         auto t = std::make_shared<Tensor2D<T>>(v.size(), v.begin()->size(), computeGrad);
//         t->set(std::forward<std::initializer_list<std::initializer_list<T>>>(v));
//         return t;
//     }
// #ifdef SCALAR_IS_TENSOR2D
//     template <typename T>
//     inline tensor<T> make_scalar(const T& t, const bool& computeGrad) {
//         return std::make_shared<Tensor2D<T>>(t, computeGrad);
//     }
// #endif

//     template <typename T>
//     tensor<T> operator+(tensor2d<T> lhs, tensor2d<T> rhs){
//         auto t = make_tensor<T>(static_cast<DMatrix<T>>(
//             lhs->data() + rhs->data()
//         ), lhs->computeGrad | rhs->computeGrad);

//         if (t->computeGrad){
//             t->initGraph({lhs, rhs}, [](std::vector<tensor<T>>& params, std::vector<tensor<T>> output) -> std::vector<tensor<T>> {
//                 return {make_scalar<T>(1), make_scalar<T>(1)};
//             });
//         }

//         return t;
//     }

//     template <typename T>
//     tensor<T> operator-(tensor2d<T> lhs, tensor2d<T> rhs){
//         auto t = make_tensor<T>(static_cast<DMatrix<T>>(
//             lhs->data() - rhs->data()
//         ), lhs->computeGrad | rhs->computeGrad);

//         if (t->computeGrad){
//             t->initGraph({lhs, rhs}, [](std::vector<tensor<T>>& params, std::vector<tensor<T>> output) -> std::vector<tensor<T>> {
//                 return {make_scalar<T>(1), make_scalar<T>(-1)};
//             });
//         }

//         return t;
//     }
    
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

#endif // __CML_TENSORS_TENSOR3D_H__
