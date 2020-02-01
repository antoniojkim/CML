#ifndef __CML_TENSORS_TENSOR_H__
#define __CML_TENSORS_TENSOR_H__

#include <ostream>

#include "TensorDecl.h"
#include "../Dtypes.h"
#include "../../utils/Random.h"
#include "../../utils/Exceptions.h"
#include "../../utils/VectorUtils.h"

namespace cml {

    template <typename T>
    class Tensor: public std::enable_shared_from_this<Tensor<T>> {

        public:
            bool computeGrad = false; // If true, creates dynamic graph on forward pass

        protected:
            std::vector<size_t> dims;
            size_t S = 0; // tensor size (i.e. number of values in the tensor)
            std::shared_ptr<T> d = nullptr; // object holding the tensor data
            std::unique_ptr<DCG<T>> dcg = nullptr;

            /*
            Note:  All constructors have been made protected to prevent object creation
                   outside of a shared pointer. The reason behind this is that the tensor
                   class inherits from std::enable_shared_from_this which requires that
                   all tensor objects exist within a shared pointer.
            */

            Tensor(const bool& computeGrad = false);
            Tensor(const std::vector<size_t>& dims, const bool& computeGrad = false);
            // Tensor(std::initializer_list<size_t> dims, const bool& computeGrad = false);
            Tensor(const DMatrix<T>& m, const bool& computeGrad = false);
            Tensor(DMatrix<T>&& m, const bool& computeGrad = false);
            template<int nDims>
            Tensor(const Eigen::Tensor<T, nDims>& t, const bool& computeGrad = false);

        public:
            MatrixMap<T> matrix();
            inline std::shared_ptr<T> data() { return d; }
            inline T* begin() { return d.get(); }
            inline T* end() { return d.get()+S; }

            template<int nDims>
            Eigen::TensorMap<Eigen::Tensor<T, nDims>> toTensor();

            inline tensor<T> getShared(){ return this->shared_from_this(); }

            template<typename... Dims>
            T& at(const Dims&... dims);
            T& at(std::initializer_list<size_t> dims);

            T& operator[](std::initializer_list<size_t> dims){
                return this->at(std::forward<std::initializer_list<size_t>>(dims));
            }
            T& operator[](const size_t& dim){ return this->at(dim); }


            T& item() {
                if (this->isScalar()) return *(d.get());
                throw CMLException("Tensor::item:  Cannot get item from non scalar tensor: ", dims);
            }

            template<size_t... dims>
            void set(nd_array<T, sizeof...(dims)> a);

            auto block(const int& startRow, const int& numRows) {
                return this->matrix().block(startRow, 0, numRows, cols());
            }
            auto block(const int& startRow, const int& startCol, const int& numRows, const int& numCols) {
                return this->matrix().block(startRow, startCol, numRows, numCols);
            }

            tensor<T> concat(tensor<T> other, const unsigned int& axis = 0);

            void fill(const T& scalar);
            void ones();
            void zero();
            void randomize(cml::Random::Function<T> r = &cml::Random::Gaussian<T>);

            tensor<T> empty(const bool& computeGrad = false);
            tensor<T> zeroLike(const bool& computeGrad = false);
            tensor<T> constant(const T& s, const bool& computeGrad = false);

            const std::vector<size_t>& shape() {
                return dims;
            };
            bool isScalar() {
                return S == 1; // dims.size() == 1 && dims[0] == 1;
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


            void initGraph(const std::vector<tensor<T>>& params = {}, GradientFunction<T> f = nullptr);
            std::unique_ptr<DCG<T>>& graph();
            tensor<T> gradient();
            void backward();

            std::ostream& print(std::ostream& out);



            tensor<T> abs();

            void apply(cml::UnaryFunction<T> f);
            tensor<T> expr(cml::UnaryFunction<T> f, const bool& computeGrad = false);

            tensor<T> matmul(tensor<T> other);
            tensor<T> mm(tensor<T> other);

            tensor<T> transpose();


            /*
                Static methods for instantiating Tensor object
            */
            static tensor<T> make_tensor(const bool& computeGrad = false);

            static tensor<T> make_tensor(const std::vector<size_t>& dims, const bool& computeGrad = false);

            // template<typename... Dims>
            // static tensor<T> make_tensor(Dims&&... dims);

            template<size_t dim, size_t... dims>
            static tensor<T> make_tensor(const bool& computeGrad = false);

            static tensor<T> make_tensor(const DMatrix<T>& m, const bool& computeGrad = false);

            template<int nDims>
            static tensor<T> make_tensor(const Eigen::Tensor<T, nDims>& t, const bool& computeGrad = false);
    };

    template<typename T>
    tensor<T> make_tensor(const bool& computeGrad = false);

    template<typename T>
    tensor<T> make_tensor(const std::vector<size_t>& dims, const bool& computeGrad = false);

    // template<typename T, typename... Dims>
    // tensor<T> make_tensor(Dims&&... dims);

    template<typename T, size_t dim, size_t... dims>
    tensor<T> make_tensor(const bool& computeGrad = false);
    template<typename T, size_t dim, size_t... dims>
    tensor<T> make_tensor(nd_array<T, sizeof...(dims)+1> a, const bool& computeGrad = false);
    template<typename T, size_t dim, size_t... dims>
    tensor<T> make_tensor(const DMatrix<T>& m, const bool& computeGrad = false);

    template <typename T>
    tensor<T> make_scalar(const T& t, const bool& computeGrad = false);
    template <typename T>
    tensor<T> make_scalar(const DMatrix<T>& m, const bool& computeGrad = false);

    template<typename T>
    tensor<T> make_tensor(const DMatrix<T>& m, const bool& computeGrad = false);
    template<typename T, int nDims>
    tensor<T> make_tensor(const Eigen::Tensor<T, nDims>& t, const bool& computeGrad = false);


}

#endif // __CML_TENSORS_TENSOR_H__
