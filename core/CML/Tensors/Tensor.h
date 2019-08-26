    #ifndef __CML_TENSORS_TENSOR_H__
#define __CML_TENSORS_TENSOR_H__

#include <ostream>

#include "TensorDecl.h"
#include "../../Utils/Random.h"
#include "../../Utils/Exceptions.h"
#include "../../Utils/VectorUtils.h"

namespace cml {

        
    template <typename U>
    cml::tensor<U> make_scalar(const U& u, const bool& computeGrad = false);

    template<typename U>
    cml::tensor<U> make_tensor(const bool& computeGrad = false);
    template<typename U>
    cml::tensor<U> make_tensor(std::vector<size_t> dims, const bool& computeGrad = false);
    template<typename U>
    cml::tensor<U> make_tensor(std::initializer_list<size_t> dims, const bool& computeGrad = false);
    template<typename U, size_t... dims>
    cml::tensor<U> make_tensor(const bool& computeGrad = false);

    template<typename U>
    cml::tensor<U> make_tensor(const DMatrix<U>& m, const bool& computeGrad = false);
    template<typename U, int nDims>
    cml::tensor<U> make_tensor(const Eigen::Tensor<U, nDims>& t, const bool& computeGrad = false);

    template <typename T>
    class Tensor: std::enable_shared_from_this<Tensor<T>> {
        
        public:
            bool computeGrad = false; // If true, creates dynamic graph on forward pass
        
        protected:
            std::vector<size_t> dims;
            size_t S = 0; // tensor size (i.e. number of values in the tensor)
            std::shared_ptr<T[]> d = nullptr; // object holding the tensor data
            std::unique_ptr<DCG<T>> dcg = nullptr;

            // Make all constructors private so that the only way to make a tensor is through
            //    the make_tensor functions.
            Tensor(const bool& computeGrad);
            Tensor(const std::vector<size_t>& dims, const bool& computeGrad);
            Tensor(std::initializer_list<size_t> dims, const bool& computeGrad);
            Tensor(const DMatrix<T>& m, const bool& computeGrad = false);
            Tensor(DMatrix<T>&& m, const bool& computeGrad = false);
            template<int nDims> 
            Tensor(const Eigen::Tensor<T, nDims>& t, const bool& computeGrad);
                
            template<size_t... dims>
            void initialize();

        public:        
            
            MatrixMap<T> matrix();
            inline std::shared_ptr<T[]> data() { return d; }

            template<int nDims>
            Eigen::TensorMap<Eigen::Tensor<T, nDims>> tensor();
        
            inline cml::tensor<T> getShared(){ return this->shared_from_this(); }

            T& at(std::initializer_list<int> dims);
        
            template<typename... Dim>
            T& at(Dim&&... dims);
            

            T& item() {
                if (this->isScalar()) return this->at(0);
                CML_THROW("Tensor::item:  Cannot get item from non scalar tensor");
            }
        
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
            void randomize(cml::Random::Function<T> r = &cml::Random::Gaussian<T>);

            cml::tensor<T> constant(const T& s, const bool& computeGrad) { 
                auto t = make_tensor<T>(dims, computeGrad);
                t.fill(s);
                return t;
            }
        
            const std::vector<size_t>& shape() {
                return dims;
            };
            bool isScalar() {
                return dims.size() == 1 && dims[0] == 1;
            }
            const size_t& size() {
                return S;
            }
            size_t numDims() {
                return dims.size();
            }

        
            void initGraph(std::vector<cml::tensor<T>> params = {}, GradientFunction<T> f = nullptr);
            std::unique_ptr<DCG<T>>& graph();
            cml::tensor<T> gradient();
            void backward();    
            
            
            void apply(T(*f)(const T& x)) {
                std::transform(d, d+S, d, f);
            }
        
        
            
            // inline cml::tensor<T> abs() {
            //     return cml::abs(this);
            // }

            // cml::tensor<T> expr(T(*f)(const T& x), const bool& computeGrad) {
            //     return make_tensor<T, nDims>(CAST_EIGEN_TENSOR(t.unaryExpr(std::ptr_fun(f))), computeGrad);
            // }

            // inline cml::tensor<T> multiply(const T& scalar) { return multiply(this, scalar); }
            // inline cml::tensor<T> multiply(cml::tensor<T> other){ return multiply(this, CAST_TENSOR_NDIMS(other.get())); }

            inline cml::tensor<T> matmul(cml::tensor<T> other){ return matmul(this->shared_from_this(), other); }
            inline cml::tensor<T> mm(cml::tensor<T> other){ return matmul(this->shared_from_this(), other); }
        
            inline cml::tensor<T> transpose(cml::tensor<T> other){ return transpose(this->shared_from_this()); }

            // inline cml::tensor<T> softmax() { return cml::Function::Softmax(this); }
            // cml::tensor<T> MSELoss(cml::tensor<T> expected, const nn::Reduction& reduction) {
            //     return cml::Function::MSELoss(this, CAST_TENSOR_NDIMS(expected.get()), reduction);
            // }
            // cml::tensor<T> CrossEntropyLoss(cml::tensor<T> expected) {
            //     return cml::Function::CrossEntropyLoss(this, CAST_TENSOR_NDIMS(expected.get()));
            // }
        
        
        
            // Declare make_tensor functions as friends of Tensor class so that they
            //     can access the private constructors
        
            template <typename U>
            friend cml::tensor<U> make_scalar(const U& u, const bool& computeGrad);

            template<typename U>
            friend cml::tensor<U> make_tensor(const bool& computeGrad);
            template<typename U>
            friend cml::tensor<U> make_tensor(std::vector<size_t> dims, const bool& computeGrad);
            template<typename U>
            friend cml::tensor<U> make_tensor(std::initializer_list<size_t> dims, const bool& computeGrad);
            template<typename U, size_t... dims>
            friend cml::tensor<U> make_tensor(const bool& computeGrad);

            template<typename U>
            friend cml::tensor<U> make_tensor(const DMatrix<U>& m, const bool& computeGrad);
            template<typename U, int nDims>
            friend cml::tensor<U> make_tensor(const Eigen::Tensor<U, nDims>& t, const bool& computeGrad);

    };  
    

}

#endif // __CML_TENSORS_TENSOR_H__
