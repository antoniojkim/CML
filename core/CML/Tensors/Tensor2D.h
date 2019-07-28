#ifndef __CML_TENSORS_TENSOR2D_H__
#define __CML_TENSORS_TENSOR2D_H__

#define SCALAR_IS_TENSOR2D
#define VECTOR_IS_TENSOR2D

#include <Eigen/Core>
#include "TensorTemplate.h"
#include "DCG.h"
#include "../Randomizer.h"

namespace cml {
    template <typename T> class Tensor2D;
    template <typename T> using tensor2d = std::shared_ptr<Tensor2D<T>>;
    
    
    template <class T, typename... Args>
    inline tensor<T> make_tensor2d(Args&&... args);
    template <typename T = float>
    inline tensor<T> make_tensor(const int& R, const int& C, const bool& computeGrad = false);
    template <class T>
    inline tensor<T> make_tensor(DMatrix<T>& m, const bool& computeGrad = false);
    template <class T>
    inline tensor<T> make_tensor(DMatrix<T>&& m, const bool& computeGrad = false);

    template <typename T>
    class Tensor2D: public Tensor<T> {
        
        DMatrix<T> m;
        
        public:
            Tensor2D(const T& t, const bool& computeGrad = false):
                Tensor<T>(computeGrad, {1, 1}, TensorType::MATRIX), m{1, 1} { fill(t); }
            Tensor2D(const int& R, const int& C, const bool& computeGrad = false):
                Tensor<T>(computeGrad, {R, C}, TensorType::MATRIX), m{R, C} {}
            Tensor2D(DMatrix<T>& m, const bool& computeGrad = false):
                Tensor<T>(computeGrad, {m.rows(), m.cols()}, TensorType::MATRIX), m{m} {}
            Tensor2D(DMatrix<T>&& m, const bool& computeGrad = false):
                Tensor<T>(computeGrad, {m.rows(), m.cols()}, TensorType::MATRIX), m{std::move(m)} {}

            inline DMatrix<T>& data() override { return m; }
        
            T& at(const int& R) override { return m(R, 0); };
            T& at(const int& R, const int& C) override { return m(R, C); }

            DBlock<T> block(const int& startCol, const int& numCols) override {
                return m.block(0, startCol, m.rows(), numCols);
            }
            DBlock<T> block(const int& startRow, const int& startCol, const int& numRows, const int& numCols){
                return m.block(startRow, startCol, numRows, numCols);
            }
        
            void set(std::initializer_list<std::initializer_list<T>> values) override {
                unsigned int i, j;

                i = 0;
                for (auto& row : values){
                    j = 0;
                    for (auto& e : row){
                        m(i, j++) = e;
                    }
                    ++i;
                }
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


    /*
        This is the recommended way to construct a matrix tensor
    */
    template <typename T = float, typename... Args>
    inline tensor<T> make_tensor2d(Args&&... args) {
        return std::make_shared<Tensor2D<T>>(std::forward<Args>(args)...);
    }
    template <typename T = float>
    inline tensor<T> make_tensor(const int& R, const int& C, const bool& computeGrad) {
        return std::make_shared<Tensor2D<T>>(R, C, computeGrad);
    }
    template <typename T = float>
    inline tensor<T> make_tensor(DMatrix<T>& m, const bool& computeGrad) {
        return std::make_shared<Tensor2D<T>>(m, computeGrad);
    }
    template <typename T = float>
    inline tensor<T> make_tensor(DMatrix<T>&& m, const bool& computeGrad) {
        return std::make_shared<Tensor2D<T>>(std::forward<DMatrix<T>&&>(m), computeGrad);
    }
#ifdef VECTOR_IS_TENSOR2D
    template <typename T = float>
    inline tensor<T> make_tensor(std::initializer_list<T> v, const bool& computeGrad = false) {
        auto t = std::make_shared<Tensor2D<T>>(1, v.size(), computeGrad);
        t->set(std::forward<std::initializer_list<T>>(v));
        return t;
    }
#endif
    template <typename T = float>
    inline tensor<T> make_tensor(std::initializer_list<std::initializer_list<T>> v, const bool& computeGrad = false) {
        auto t = std::make_shared<Tensor2D<T>>(v.size(), v.begin()->size(), computeGrad);
        t->set(std::forward<std::initializer_list<std::initializer_list<T>>>(v));
        return t;
    }
#ifdef SCALAR_IS_TENSOR2D
    template <typename T>
    inline tensor<T> make_scalar(const T& t, const bool& computeGrad) {
        return std::make_shared<Tensor2D<T>>(t, computeGrad);
    }
#endif

    template <typename T>
    tensor<T> operator+(tensor2d<T> lhs, tensor2d<T> rhs){
        auto t = make_tensor<T>(static_cast<DMatrix<T>>(
            lhs->data() + rhs->data()
        ), lhs->computeGrad | rhs->computeGrad);

        if (t->computeGrad){
            t->initGraph({lhs, rhs}, [](std::vector<tensor<T>>& params, std::vector<tensor<T>> output) -> std::vector<tensor<T>> {
                return {make_scalar<T>(1), make_scalar<T>(1)};
            });
        }

        return t;
    }

    template <typename T>
    tensor<T> operator-(tensor2d<T> lhs, tensor2d<T> rhs){
        auto t = make_tensor<T>(static_cast<DMatrix<T>>(
            lhs->data() - rhs->data()
        ), lhs->computeGrad | rhs->computeGrad);

        if (t->computeGrad){
            t->initGraph({lhs, rhs}, [](std::vector<tensor<T>>& params, std::vector<tensor<T>> output) -> std::vector<tensor<T>> {
                return {make_scalar<T>(1), make_scalar<T>(-1)};
            });
        }

        return t;
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
