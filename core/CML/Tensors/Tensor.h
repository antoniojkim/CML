#ifndef __CML_TENSORS_TENSOR_H__
#define __CML_TENSORS_TENSOR_H__

#include <ostream>

#include <Eigen/Core>
#include <unsupported/Eigen/CXX11/Tensor>

#include "TensorBase.h"
#include "../Functions/TensorOps/TensorOps.h"
#include "../Functions/NonLinear/NonLinear.h"

namespace cml {

    template <typename T, int nDims> class Tensor;

    #ifndef CAST_TENSOR
    #define CAST_TENSOR static_cast<Eigen::Tensor<T, nDims>>
    #endif // CAST_TENSOR


    template <typename T, int nDims>
    class Tensor: public TensorBase<T>{
        
        protected:
            Eigen::Tensor<T, nDims> t;

        public:

            Tensor(const bool& computeGrad = false): 
                TensorBase(computeGrad) {}
            Tensor(Tensor<T, nDims>&& other, const bool& computeGrad = false): 
                TensorBase(computeGrad), t{std::move(other)} {}
            Tensor(std::initializer_list<int> d, const bool& computeGrad = false): 
                TensorBase(computeGrad), t{d} {}
            Tensor(DMatrix<T>&& other, const bool& computeGrad = false): 
                TensorBase(computeGrad),
                t{std::move(Eigen::TensorMap<Eigen::Tensor<const T, 2>>(m.data(), {m.rows(), m.cols()}))} {}

            // template<typename... Args>
            // Tensor(Args&&... args): t{std::forward<Args>(args)...} {}
            
            inline MatrixMap<T> matrix() override {
                auto R = t.dimension(0);
                auto C = t.size() / R;
                return Eigen::Map<DMatrix<T>>(t.data(), R, C);
            }
            inline T* data() override { return t.data(); }
            inline Eigen::Tensor<T, nDims>& tensor(){ return t; }

            T& at(const int& d1) override { return t(d1); }
            T& at(const int& d1, const int& d2) override { return t(d1, d2); }
            T& at(const int& d1, const int& d2, const int& d3) override { return t(d1, d2, d3); }
            T& at(const int& d1, const int& d2, const int& d3, const int& d4) override { return t(d1, d2, d3, d4); }

            DBlock<T> block(const int& startCol, const int& numCols) override {
                return this->matrix().block(0, startCol, dimensions.rows(), numCols);
            }
            DBlock<T> block(const int& startRow, const int& startCol, const int& numRows, const int& numCols) override {
                return this->matrix().block(startRow, startCol, numRows, numCols);
            }

            /*
                Due to limitations of C++ template type deduction, cannot make a set
                function that takes in an arbitrary dimension initializer list.
                To explicitly set values, one must go through the tensor variable itself.
                i.e.
                    t.data().setValues(...);
             */

            void fill(const T& coefficient) override { t.setConstant(coefficient); }
            void ones() override { t.setOnes(); }
            void zero() override { t.setZero(); }
            void randomize(const unsigned int& seed) override { srand(seed); t.setRandom(); }

            tensor<T> constant(const T& s, const bool& computeGrad) override { 
                return make_tensor<T, nDims>(t.constant(s), computeGrad);
            }
        
            std::vector<int> shape() override {
                auto d = t.dimensions();
                return vector<int>(std::begin(d), std::end(d));
            };
            bool isScalar() override {
                const auto& dims = t.dimensions();
                return dims.size == 1 && dims[0] == 1;
            }
            int size() override {
                return t.size();
            }
            int numDims() override {
                return t.NumDimensions;
            }



            
            void apply(T(*f)(const T& x)) override {
                t = t.unaryExpr(std::ptr_fun(f));
            }
            inline tensor<T> abs() override {
                return cml::abs(this);
            }

            tensor<T> expr(T(*f)(const T& x)) override {
                return make_tensor<T, nDims>(t.unaryExpr(std::ptr_fun(f)), computeGrad);
            }

            tensor<T> multiply(tensor<T> other){
                if (other.numDims() != nDims) throw "Invalid coefficient-wise multiplication";
                auto o = static_cast<Tensor<T, nDims>*>(other.get());
                return make_tensor<T, nDims>(t * o->t, computeGrad);
            }

            inline auto matmul(tensor<T> other){
                return matmul(this, other.get());
            }
            inline auto mm(tensor<T> other){
                return matmul(this, other.get());
            }

            inline tensor<T> softmax() override {
                return cml::Functions::Softmax(this);
            }
    };

    template<typename T, typename nDims>
    std::ostream& operator<<(std::ostream& out, Tensor<T, nDims>* t){
        return out << t.tensor();
    }
    
    template<typename T> using Tensor1D = Tensor<T, 1>;
    template<typename T> using Tensor2D = Tensor<T, 2>;
    template<typename T> using Tensor3D = Tensor<T, 3>;
    template<typename T> using Tensor4D = Tensor<T, 4>;

    template<typename T> using tensor1d = std::shared_ptr<Tensor1D<T>>;
    template<typename T> using tensor2d = std::shared_ptr<Tensor2D<T>>;
    template<typename T> using tensor3d = std::shared_ptr<Tensor3D<T>>;
    template<typename T> using tensor4d = std::shared_ptr<Tensor4D<T>>;


    template <typename T = float, typename nDims>
    inline tensor<T> make_scalar(const T& t, const bool& computeGrad = false){
        auto u = std::make_shared<Tensor1D<T>>(d1, computeGrad);
        u->item() = t;
        return u;
    }

    // template<typename T, typename nDims, typename... Args>
    // tensor<T> make_tensor(Args&&... args){
    //     return std::make_shared<Tensor<T, nDims>>(std::forward<Args>(args)...);
    // }
    
    template<typename T>
    tensor<T> make_tensor(const int& d1, const bool& computeGrad = false){
        return std::make_shared<Tensor1D<T>>({d1}, computeGrad);
    }
    template<typename T>
    tensor<T> make_tensor(const int& d1, const int& d2, const bool& computeGrad = false){
        return std::make_shared<Tensor2D<T>>({d1, d2}, computeGrad);
    }
    template<typename T>
    tensor<T> make_tensor(const int& d1, const int& d2, const int& d3, const bool& computeGrad = false){
        return std::make_shared<Tensor3D<T>>({d1, d2, d3}, computeGrad);
    }
    template<typename T>
    tensor<T> make_tensor(const int& d1, const int& d2, const int& d3, const int& d4, const bool& computeGrad = false){
        return std::make_shared<Tensor4D>>({d1, d2, d3, d4}, computeGrad);
    }

    template<typename T, typename nDims>
    tensor<T> make_tensor(Tensor<T, nDims>&& other, const bool& computeGrad = false){
        return std::make_shared<Tensor<T, nDims>>(std::forward<Tensor<T, nDims>&&>(other), computeGrad);
    }
    template<typename T>
    tensor<T> make_tensor(DMatrix&& other, const bool& computeGrad = false){
        return std::make_shared<Tensor<T, 2>>(std::move(other), computeGrad);
    }
    
    

}

#endif // __CML_TENSORS_TENSOR_H__
