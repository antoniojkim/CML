#ifndef __CML_TENSORS_TENSOR2D_H__
#define __CML_TENSORS_TENSOR2D_H__

#include <Eigen/Core>
#include "TensorTemplate.h"
#include "DCG.h"
#include "../Randomizer.h"

namespace cml {
    template <typename T> class Tensor2D;
    template <typename T> using tensor2d = std::shared_ptr<Tensor2D<T>>;
    
    
    template <class T, typename... Args>
    tensor<T> make_tensor2d(Args&&... args);
    template <class T>
    tensor<T> make_tensor(DMatrix<T>& m, const bool& computeGrad = false);
    template <class T>
    tensor<T> make_tensor(DMatrix<T>&& m, const bool& computeGrad = false);

    template <typename T>
    class Tensor2D: public Tensor<T> {
        
        DMatrix<T> m;
        
        public:
            Tensor2D(const T& t, const bool& computeGrad = false):
                Tensor<T>({1, 1}, TensorType::MATRIX, computeGrad), m{1, 1} { fill(t); }
            Tensor2D(const int& R, const int& C, const bool& computeGrad = false):
                Tensor<T>({R, C}, TensorType::MATRIX, computeGrad), m{R, C} {}
            Tensor2D(DMatrix<T>& m, const bool& computeGrad = false):
                Tensor<T>({m.rows(), m.cols()}, TensorType::MATRIX, computeGrad), m{m} {}
            Tensor2D(DMatrix<T>&& m, const bool& computeGrad = false):
                Tensor<T>({m.rows(), m.cols()}, TensorType::MATRIX, computeGrad), m{m} {}

            inline DMatrix<T>& data() override { return m; }
        
            T& at(const int& R) override { return m(R, 0); };
            T& at(const int& R, const int& C) override { return m(R, C); }
            T& at(const int& C, const int& H, const int& W) override {
                throw "Tensor2D::at:   Channel does not exist";
            }
        
        
            void set(std::initializer_list<T> values, const bool& transpose = false) override {
                unsigned int i = 0;
                if (transpose){
                    for (auto& e : values) {
                        m(0, i++) = e;
                    }
                }
                else{
                    for (auto& e : values) {
                        m(i++, 0) = e;
                    }
                }
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
            void set(std::initializer_list<std::initializer_list<std::initializer_list<T>>> values) {
                throw "Cannot use 3D initializer_list to set values of Tensor2D";
            }

            inline void fill(const T& coefficient) override { m.setConstant(coefficient); }
            inline void ones() override { m.setOnes(); }
            inline void zero() override { m.setZero(); }
            inline void randomize() override { m.setRandom(); }
        
            tensor<T> emptyCopy() override {
                return make_tensor2d<T>(m.rows(), m.cols(), false);
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
        return std::make_shared<Tensor2D<T>>(std::forward<DMatrix<T>>(m), computeGrad);
    }
#if VECTOR_TENSOR_DIM==2
    template <typename T = float>
    inline tensor<T> make_tensor(std::initializer_list<T> v, const bool& computeGrad = false) {
        auto t = std::make_shared<Tensor2D<T>>(v.size(), 1, computeGrad);
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
#if SCALAR_TENSOR_DIM==2
    template <typename T = float>
    inline tensor<T> make_scalar(const T& t, const bool& computeGrad = false) {
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

    template <typename T>
    tensor<T> operator*(tensor2d<T> lhs, tensor2d<T> rhs){
        auto t = make_tensor<T>(static_cast<DMatrix<T>>(
            lhs->data() * rhs->data()
        ), lhs->computeGrad | rhs->computeGrad);

        if (t->computeGrad){
            t->initGraph({lhs, rhs}, [](std::vector<tensor<T>>& params, std::vector<tensor<T>> output) -> std::vector<tensor<T>> {
#ifdef DEBUG
                using namespace std;
                cout << "Tensor2D Multiplication Backward" << endl;
#endif
                auto lhs = params.at(0);
                auto rhs = params.at(1);
                auto output_grad = output.at(0);
                tensor<T> lhs_grad = nullptr;
                tensor<T> rhs_grad = nullptr;

                if (lhs->computeGrad){
                    lhs_grad = make_tensor<T>(static_cast<DMatrix<T>>(
                        // TODO:  Check to see if order is correct
                        output_grad->data() * rhs->data()->transpose()
                    ));
                }
                if (rhs->computeGrad){
                    rhs_grad = make_tensor<T>(static_cast<DMatrix<T>>(
                        // TODO:  Check to see if order is correct
                        lhs->data()->transpose() * output_grad->data()
                    ));
                }

                return {lhs_grad, rhs_grad};
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
