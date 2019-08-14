#ifndef __CML_TENSORS_TENSOR_H__
#define __CML_TENSORS_TENSOR_H__

#include <ostream>

#include <Eigen/Core>
#include <unsupported/Eigen/CXX11/Tensor>

#include "TensorDecl.h"
#include "TensorBase.h"
#include "../Functions/TensorOps/TensorOps.h"
#include "../Functions/NonLinear/NonLinear.h"
#include "../Functions/Loss/Loss.h"

namespace cml {


    template <typename T, int nDims>
    class Tensor: public TensorBase<T>{
        
        protected:
            Eigen::Tensor<T, nDims> t;

        public:

            Tensor(const bool& computeGrad): TensorBase<T>(computeGrad) {}
            Tensor(Tensor<T, nDims>&& other, const bool& computeGrad):  TensorBase<T>(computeGrad), t{std::move(other)} {}
            Tensor(std::initializer_list<int> d, const bool& computeGrad):  TensorBase<T>(computeGrad), t{d} {}
            Tensor(DMatrix<T>&& m, const bool& computeGrad): TensorBase<T>(computeGrad),
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

            inline void set(std::initializer_list<T> values) override { t->setValues(values); }
            inline void set(std::initializer_list<std::initializer_list<T>> values) override { t->setValues(values); }

            DBlock<T> block(const int& startCol, const int& numCols) override {
                return this->matrix().block(0, startCol, t.dimension(0), numCols);
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

            cml::tensor<T> constant(const T& s, const bool& computeGrad) override { 
                return make_tensor<T, nDims>(t.constant(s), computeGrad);
            }
        
            std::vector<int> shape() override {
                auto d = t.dimensions();
                return std::vector<int>(std::begin(d), std::end(d));
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
            inline cml::tensor<T> abs() override {
                return cml::abs(this);
            }

            cml::tensor<T> expr(T(*f)(const T& x), const bool& computeGrad) override {
                return make_tensor<T, nDims>(CAST_EIGEN_TENSOR(t.unaryExpr(std::ptr_fun(f))), computeGrad);
            }

            inline cml::tensor<T> multiply(const T& scalar) override { return multiply(this, scalar); }
            inline cml::tensor<T> multiply(cml::tensor<T> other){ return multiply(this, CAST_TENSOR_NDIMS(other.get())); }

            inline auto matmul(cml::tensor<T> other){ return matmul(this, other.get()); }
            inline auto mm(cml::tensor<T> other){ return matmul(this, other.get()); }

            inline cml::tensor<T> softmax() override { return cml::Function::Softmax(this); }
            cml::tensor<T> MSELoss(cml::tensor<T> expected, const nn::Reduction& reduction) override {
                return cml::Function::MSELoss(this, CAST_TENSOR_NDIMS(expected.get()), reduction);
            }
            cml::tensor<T> CrossEntropyLoss(cml::tensor<T> expected) {
                return cml::Function::CrossEntropyLoss(this, CAST_TENSOR_NDIMS(expected.get()));
            }
    };


    // template<typename T, int nDims>
    // cml::tensor<T> Tensor<T, nDims>::multiply(cml::tensor<T> other){
    //     if (other.numDims() != nDims) throw "Invalid coefficient-wise multiplication";
    //     auto o = static_cast<Tensor<T, nDims>*>(other.get());
    //     return make_tensor<T, nDims>(CAST_EIGEN_TENSOR(t * o->t), computeGrad);
    // }

    template<typename T, int nDims>
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


    template <typename T>
    inline tensor<T> make_scalar(const T& t, const bool& computeGrad){
        auto u = std::make_shared<Tensor1D<T>>(1, computeGrad);
        u->item() = t;
        return u;
    }

    // template<typename T, typename nDims, typename... Args>
    // tensor<T> make_tensor(Args&&... args){
    //     return std::make_shared<Tensor<T, nDims>>(std::forward<Args>(args)...);
    // }
    
    template<typename T>
    inline tensor<T> make_tensor(const int& d1, const bool& computeGrad){
        return std::make_shared<Tensor1D<T>>({d1}, computeGrad);
    }
    template<typename T>
    inline tensor<T> make_tensor(const int& d1, const int& d2, const bool& computeGrad){
        return std::make_shared<Tensor2D<T>>({d1, d2}, computeGrad);
    }
    template<typename T>
    inline tensor<T> make_tensor(const int& d1, const int& d2, const int& d3, const bool& computeGrad){
        return std::make_shared<Tensor3D<T>>({d1, d2, d3}, computeGrad);
    }
    template<typename T>
    inline tensor<T> make_tensor(const int& d1, const int& d2, const int& d3, const int& d4, const bool& computeGrad){
        return std::make_shared<Tensor4D<T>>({d1, d2, d3, d4}, computeGrad);
    }


    template<typename T>
    inline ntensor<T, 1> make_ntensor(const int& d1, const bool& computeGrad){
        return std::make_shared<Tensor1D<T>>({d1}, computeGrad);
    }
    template<typename T>
    inline ntensor<T, 2> make_ntensor(const int& d1, const int& d2, const bool& computeGrad){
        return std::make_shared<Tensor2D<T>>({d1, d2}, computeGrad);
    }
    template<typename T>
    inline ntensor<T, 3> make_ntensor(const int& d1, const int& d2, const int& d3, const bool& computeGrad){
        return std::make_shared<Tensor3D<T>>({d1, d2, d3}, computeGrad);
    }
    template<typename T>
    inline ntensor<T, 4> make_ntensor(const int& d1, const int& d2, const int& d3, const int& d4, const bool& computeGrad){
        return std::make_shared<Tensor4D<T>>({d1, d2, d3, d4}, computeGrad);
    }

    template<typename T>
    inline tensor<T> make_tensor(std::initializer_list<T> values, const bool& computeGrad){
        auto t = std::make_shared<Tensor1D<T>>({values.size()}, computeGrad);
        t->tensor()->setValues(values);
        return t;
    }
    template<typename T>
    inline tensor<T> make_tensor(std::initializer_list<std::initializer_list<T>> values, const bool& computeGrad){
        auto t = std::make_shared<Tensor2D<T>>({values.size(), values.begin().size()}, computeGrad);
        t->tensor()->setValues(values);
        return t;
    }

    template<typename T, int nDims>
    inline tensor<T> make_tensor(Tensor<T, nDims>&& other, const bool& computeGrad = false){
        return std::make_shared<Tensor<T, nDims>>(std::forward<Tensor<T, nDims>&&>(other), computeGrad);
    }
    template<typename T>
    inline tensor<T> make_tensor(DMatrix<T>&& other, const bool& computeGrad = false){
        return std::make_shared<Tensor<T, 2>>(std::move(other), computeGrad);
    }
    
    

}

#endif // __CML_TENSORS_TENSOR_H__
