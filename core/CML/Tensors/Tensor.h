#ifndef __CML_TENSORS_TENSOR_H__
#define __CML_TENSORS_TENSOR_H__

#include <functional>
#include <ostream>

#include "TensorDecl.h"
#include "../../Utils/Random.h"
#include "../../Utils/Exceptions.h"
#include "../../Utils/VectorUtils.h"

namespace cml {    

    template <typename T>
    class Tensor: std::enable_shared_from_this<Tensor<T>> {
        
        public:
            bool computeGrad = false; // If true, creates dynamic graph on forward pass
        
        protected:
            std::vector<size_t> dims;
            size_t S = 0; // tensor size (i.e. number of values in the tensor)
            std::shared_ptr<T> d = nullptr; // object holding the tensor data
            std::unique_ptr<DCG<T>> dcg = nullptr;    


        public:
            /*
            Note:  While the constructors are public, it is not recommended
                   to create a Tensor object outside of a shared pointer
                   as Tensor inherits from std::enable_shared_from_this.
                   Always create tensor objects using only the make_tensor
                   functions provided.
            */
        
            Tensor(const bool& computeGrad = false);
            Tensor(const std::vector<size_t>& dims, const bool& computeGrad = false);
            Tensor(std::initializer_list<size_t> dims, const bool& computeGrad = false);
            Tensor(const DMatrix<T>& m, const bool& computeGrad = false);
            Tensor(DMatrix<T>&& m, const bool& computeGrad = false);
            template<int nDims>
            Tensor(const Eigen::Tensor<T, nDims>& t, const bool& computeGrad = false);
            
            MatrixMap<T> matrix();
            inline std::shared_ptr<T> data() { return d; }

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
        
            template<size_t... dims>
            void set(nd_array<T, sizeof...(dims)> a);

            DBlock<T> block(const int& startCol, const int& numCols) {
                return this->matrix().block(0, startCol, dims[0], numCols);
            }
            DBlock<T> block(const int& startRow, const int& startCol, const int& numRows, const int& numCols) {
                return this->matrix().block(startRow, startCol, numRows, numCols);
            }

            void fill(const T& scalar);
            void ones();
            void zero();
            void randomize(cml::Random::Function<T> r = &cml::Random::Gaussian<T>);

            cml::tensor<T> empty(const bool& computeGrad = false);
            cml::tensor<T> zeroLike(const bool& computeGrad = false);
            cml::tensor<T> constant(const T& s, const bool& computeGrad = false);
        
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
            inline const size_t& rows() {
                return dims[0];
            }
            inline size_t cols() {
                return dims.size() == 2 ? dims[1] : (S / dims[0]);
            }

        
            void initGraph(const std::vector<cml::tensor<T>>& params = {}, GradientFunction<T> f = nullptr);
            std::unique_ptr<DCG<T>>& graph();
            cml::tensor<T> gradient();
            void backward();
            
            
        
        
            
            cml::tensor<T> abs();

            void apply(cml::UnaryFunction<T> f);
            cml::tensor<T> expr(cml::UnaryFunction<T> f, const bool& computeGrad = false);

            cml::tensor<T> matmul(cml::tensor<T> other);
            cml::tensor<T> mm(cml::tensor<T> other);
        
            cml::tensor<T> transpose();
        
        
            /*
                Static methods for instantiating Tensor object
            */
            static cml::tensor<T> make_tensor(std::vector<size_t> dims, const bool& computeGrad = false);
        
            template<typename... Dims>
            static cml::tensor<T> make_tensor(Dims&&... dims, const bool& computeGrad = false);

            template<size_t... dims>
            static cml::tensor<T> make_tensor(const bool& computeGrad = false);

            static cml::tensor<T> make_tensor_from(const DMatrix<T>& m, const bool& computeGrad = false);

            template<int nDims>
            static cml::tensor<T> make_tensor_from(const Eigen::Tensor<T, nDims>& t, const bool& computeGrad = false);

    };

    template<typename T>
    cml::tensor<T> make_tensor(std::vector<size_t> dims, const bool& computeGrad = false);
    template<typename T, typename... Dims>
    cml::tensor<T> make_tensor(Dims&&... dims);
    template<typename T, size_t... dims>
    cml::tensor<T> make_tensor(const bool& computeGrad = false);
    template<typename T, size_t... dims>
    cml::tensor<T> make_tensor(nd_array<T, sizeof...(dims)> a, const bool& computeGrad = false);
    
    template <typename T>
    cml::tensor<T> make_scalar(const T& t, const bool& computeGrad = false);

    template<typename T>
    cml::tensor<T> make_tensor_from(const DMatrix<T>& m, const bool& computeGrad = false);
    template<typename T, int nDims>
    cml::tensor<T> make_tensor_from(const Eigen::Tensor<T, nDims>& t, const bool& computeGrad = false);
    

}

#endif // __CML_TENSORS_TENSOR_H__
