#ifndef __CML_TENSORS_TENSOR_H__
#define __CML_TENSORS_TENSOR_H__

#include <ostream>

#include <Eigen/Core>
#include <unsupported/Eigen/CXX11/Tensor>

#include "TensorBase.h"

namespace cml {



    template <typename T, typename nDims> class Tensor;
    template <typename T, typename nDims> class DCG;  // Dynamic Compute Graph


    template <typename T, typename nDims>
    class Tensor{
        
        protected:
            Eigen::Tensor<T, nDims> t;
            TensorDimension dimensions;
            std::unique_ptr<DCG<T, nDims>> dcg = nullptr;

        public:

            Tensor(const bool& computeGrad = false): 
                TensorBase(computeGrad) {}
            Tensor(Tensor<T, nDims>&& other, const bool& computeGrad = false): 
                TensorBase(computeGrad, other.dimensions()), t{std::move(other)} {}
            Tensor(initializer_list<int> d, const bool& computeGrad = false): 
                TensorBase(computeGrad, d), t{d} {}

            // template<typename... Args>
            // Tensor(Args&&... args): t{std::forward<Args>(args)...} {}
            
            inline MapMatrix<T> matrix() override {
                constexpr auto R = t.dimension(0);
                constexpr auto C = t.size() / R;
                return Eigen::Map<DMatrix<T>>(t.data(), R, C);
            }
            Eigen::Tensor<T, nDims>& data() { return t; }

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
        
            vector<int> shape() override { return std::vector<int>(t.dimensions()); };
            bool isScalar() override {
                const auto& dims = t.dimensions();
                return dims.size == 1 && dims[0] == 1;
            }
            int size() override {
                return t.size();
            }


            inline tensor<T, nDims> matmul(tensor<T, nDims> other){
                return matmul(this, other.get());
            }
            inline tensor<T, nDims> mm(tensor<T, nDims> other){
                return matmul(this, other.get());
            }
    };

    
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
        return std::make_shared<Tensor<T, nDims>>(std::move(other), computeGrad);
    }

}

#endif // __CML_TENSORS_TENSOR_H__
