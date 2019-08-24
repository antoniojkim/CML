#ifndef __CML_TENSORS_TENSOR_H__
#define __CML_TENSORS_TENSOR_H__

#include <ostream>

#include "TensorDecl.h"
#include "../../Utils/VectorUtils.h"

namespace cml {


    template <typename T>
    class Tensor {
        
        public:
            bool computeGrad = false; // If true, creates dynamic graph on forward pass
        
        protected:
            std::vector<size_t> dims;
            size_t S = 0; // tensor size (i.e. number of values in the tensor)
            std::shared_ptr<T[]> d = nullptr; // object holding the tensor data
            std::unique_ptr<DCG<T>> dcg = nullptr;

        public:

            Tensor(const bool& computeGrad);
            Tensor(const std::vector<size_t>& dims, const bool& computeGrad = false);
            Tensor(std::initializer_list<size_t> dims, const bool& computeGrad = false);
            Tensor(const DMatrix<T>& m, const bool& computeGrad = false);
            template<int nDims> 
            Tensor(const Eigen::Tensor<T, nDims>& t, const bool& computeGrad = false);
                
            template<size_t... dims>
            void initialize();
            
            MatrixMap<T> matrix();
            inline std::shared_ptr<T[]> data() { return d; }

            template<int nDims>
            Eigen::TensorMap<Eigen::Tensor<T, nDims>> tensor();

            T& at(std::initializer_list<int> dims);

            void set(std::initializer_list<T> values);
            void set(std::initializer_list<std::initializer_list<T>> values);

            DBlock<T> block(const int& startCol, const int& numCols) {
                return this->matrix().block(0, startCol, dims[0], numCols);
            }
            DBlock<T> block(const int& startRow, const int& startCol, const int& numRows, const int& numCols) {
                return this->matrix().block(startRow, startCol, numRows, numCols);
            }

            void fill(const T& coefficient);
            void ones();
            void zero();
            void randomize(const unsigned int& seed);

            cml::tensor<T> constant(const T& s, const bool& computeGrad) override { 
                return make_tensor<T, nDims>(t.constant(s), computeGrad);
            }
        
            const std::vector<size_t>& shape() override {
                return dims;
            };
            bool isScalar() override {
                const auto& dims = t.dimensions();
                return dims.size == 1 && dims[0] == 1;
            }
            const size_t& size() override {
                return S;
            }
            size_t numDims() override {
                return dims.size();
            }



            
            void apply(T(*f)(const T& x)) override {
                t = t.unaryExpr(std::ptr_fun(f));
            }
            // inline cml::tensor<T> abs() override {
            //     return cml::abs(this);
            // }

            // cml::tensor<T> expr(T(*f)(const T& x), const bool& computeGrad) override {
            //     return make_tensor<T, nDims>(CAST_EIGEN_TENSOR(t.unaryExpr(std::ptr_fun(f))), computeGrad);
            // }

            // inline cml::tensor<T> multiply(const T& scalar) override { return multiply(this, scalar); }
            // inline cml::tensor<T> multiply(cml::tensor<T> other){ return multiply(this, CAST_TENSOR_NDIMS(other.get())); }

            // inline auto matmul(cml::tensor<T> other){ return matmul(this, other.get()); }
            // inline auto mm(cml::tensor<T> other){ return matmul(this, other.get()); }

            // inline cml::tensor<T> softmax() override { return cml::Function::Softmax(this); }
            // cml::tensor<T> MSELoss(cml::tensor<T> expected, const nn::Reduction& reduction) override {
            //     return cml::Function::MSELoss(this, CAST_TENSOR_NDIMS(expected.get()), reduction);
            // }
            // cml::tensor<T> CrossEntropyLoss(cml::tensor<T> expected) {
            //     return cml::Function::CrossEntropyLoss(this, CAST_TENSOR_NDIMS(expected.get()));
            // }
    };

    // template<typename T, int nDims>
    // cml::tensor<T> Tensor<T, nDims>::multiply(cml::tensor<T> other){
    //     if (other.numDims() != nDims) throw "Invalid coefficient-wise multiplication";
    //     auto o = static_cast<tensor<T>>(other.get());
    //     return make_tensor<T, nDims>(CAST_EIGEN_TENSOR(t * o->t), computeGrad);
    // }

    template<typename T, int nDims>
    std::ostream& operator<<(std::ostream& out, Tensor<T>* t){
        return out << t->matrix();
    }


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
