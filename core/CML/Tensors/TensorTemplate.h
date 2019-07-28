#ifndef __CML_TENSORS_TENSOR_H__
#define __CML_TENSORS_TENSOR_H__

#include <ctime>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <memory>
#include <vector>

#include "TensorDimension.h"
#include "../../Utils/Exceptions.h"
#include "../../Utils/TypeName.h"

namespace cml {

    template <typename T> class Tensor;
    template <typename T> class DCG;  // Dynamic Compute Graph

    /*
        Note that the lower case tensor is used for a shared_ptr to a Tensor object.
        Lowercase as it isn't a direct reference, but rather an indirect one.
    */
    template <typename T>
    using tensor = std::shared_ptr<Tensor<T>>;

    template <typename T>
    using DMatrix = Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>;  // Dynamic Matrix
    template <typename T>
    using RefMatrix = Eigen::Ref<DMatrix<T>>;  // Ref to Dynamic Matrix
    template <typename T>
    using DBlock = Eigen::Block<DMatrix<T>, Eigen::Dynamic, Eigen::Dynamic, false>;  // Dynamic Block
    template <typename T>
    using DArray = Eigen::Array<T, Eigen::Dynamic, Eigen::Dynamic>;  // Dynamic Array

    template <typename T>
    using GradientFunction = std::function<std::vector<tensor<T>>(std::vector<tensor<T>>&,
                                                                  std::vector<tensor<T>>)>;

    enum TensorType {
        NONE,
        SCALAR,
        VECTOR,
        MATRIX,
        _3D_,
        _4D_,
    };

    template<typename T>
    class Tensor {
        
        public:
            bool computeGrad = false; // If true, creates dynamic graph on forward pass
        
        protected:
            std::unique_ptr<DCG<T>> dcg = nullptr;
            TensorDimension dimensions;
            TensorType type = TensorType::NONE;
        
            Tensor(const bool& computeGrad, std::initializer_list<int> v, TensorType type):
                computeGrad{computeGrad}, dimensions{std::forward<std::initializer_list<int>>(v)}, type{type} {}
            Tensor(const bool& computeGrad, std::vector<int>& v, TensorType type):
                computeGrad{computeGrad}, dimensions{v}, type{type} {}
        
        public:
            
            virtual DMatrix<T>& data() = 0;
            T& item() {
                if (this->isScalar()) return this->at(0);
                throw "Tensor::item:  Cannot get item from non scalar tensor";
            }
            
            /*
                Get coefficients for vector tensors where:
                    - "R" is the row number
            */
            virtual T& at(const int& R) {
                throw UnsupportedOperationException(type_name<decltype(*this)>() + "::at(int)");
            }
            /*
                Get coefficients for matrix tensors where:
                    - "R" is the row number
                    - "C" is the column number
            */
            virtual T& at(const int& R, const int& C) {
                throw UnsupportedOperationException(type_name<decltype(*this)>() + "::at(int, int)");
            }
            /*
                Get coefficients for 3d tensors where:
                    - "C" is the channel number
                    - "H" is the height
                    - "W" is the width
            */
            virtual T& at(const int& C, const int& H, const int& W) {
                throw UnsupportedOperationException(type_name<decltype(*this)>() + "::at(int, int, int)");
            }
        
            inline T& operator()(const int& R){ return this->at(R); }
            inline T& operator()(const int& R, const int& C){ return this->at(R, C); }
            inline T& operator()(const int& C, const int& H, const int& W){ return this->at(C, H, W); }
        
            inline T& data(const int& R){ return this->at(R); }
            inline T& data(const int& R, const int& C){ return this->at(R, C); }
            inline T& data(const int& C, const int& H, const int& W){ return this->at(C, H, W); }
            
            virtual DBlock<T> block(const int& startCol, const int& numCols) {
                throw UnsupportedOperationException(type_name<decltype(*this)>() + "::block(int, int)");
            }
            virtual DBlock<T> block(const int& startRow, const int& startCol, const int& numRows, const int& numCols) {
                throw UnsupportedOperationException(type_name<decltype(*this)>() + "::block(int, int, int, int)");
            }

            virtual tensor<T> transpose() {
                throw UnsupportedOperationException(type_name<decltype(*this)>() + "::transpose()");
            }
            
            virtual void set(std::initializer_list<T> values, const bool& transpose = false) {
                throw UnsupportedOperationException(type_name<decltype(*this)>() + "::set(1D Initializer List)");
            }
            virtual void set(std::initializer_list<std::initializer_list<T>> values) {
                throw UnsupportedOperationException(type_name<decltype(*this)>() + "::set(2D Initializer List)");
            }
            virtual void set(std::initializer_list<std::initializer_list<std::initializer_list<T>>> values) {
                throw UnsupportedOperationException(type_name<decltype(*this)>() + "::set(3D Initializer List)");
            }
            
            inline void operator=(std::initializer_list<T> values){
                this->set(std::forward<std::initializer_list<T>>(values));
            };
            inline void operator=(std::initializer_list<std::initializer_list<T>> values){
                this->set(std::forward<std::initializer_list<std::initializer_list<T>>>(values));
            };
            inline void operator=(std::initializer_list<std::initializer_list<std::initializer_list<T>>> values){
                this->set(std::forward<std::initializer_list<std::initializer_list<std::initializer_list<T>>>>(values));
            };
        
            virtual void fill(const T& coefficient){
                throw UnsupportedOperationException(type_name<decltype(*this)>() + "::fill()");
            }
            virtual void ones(){
                throw UnsupportedOperationException(type_name<decltype(*this)>() + "::ones()");
            }
            virtual void zero(){
                throw UnsupportedOperationException(type_name<decltype(*this)>() + "::zero()");
            }
            virtual void randomize(const unsigned int& seed = time(NULL)) {
                throw UnsupportedOperationException(type_name<decltype(*this)>() + "::randomize()");
            }
            virtual void randomize(const Eigen::VectorXi& indices) {
                throw UnsupportedOperationException(type_name<decltype(*this)>() + "::randomize(Eigen::VectorXi)");
            }
        
            virtual tensor<T> zeroLike() {
                throw UnsupportedOperationException(type_name<decltype(*this)>() + "::zeroLike()");
            }
        
            inline TensorDimension& dims() { return dimensions; }
            inline TensorDimension& shape() { return dimensions; }
            inline bool isScalar() { return dimensions.isScalar(); }
            inline unsigned int size() { return dimensions.size(); }
            virtual inline int rows(){ return dimensions.size(); }
            virtual inline int cols(){ return dimensions.numBatches(); }

            TensorType getType(){ return type; }
        
        
            void initGraph(std::vector<tensor<T>> params = {}, GradientFunction<T> f = nullptr){
                if (!dcg) {
                    dcg = std::make_unique<DCG<T>>(this, std::forward<std::vector<tensor<T>>>(params),
                                                   std::forward<GradientFunction<T>>(f));
                } else {
                    throw "Called initGraph when graph already exists";
                }
            }
            std::unique_ptr<DCG<T>>& graph(){
                if (!dcg) {
                    if (!computeGrad) throw "Getting graph of tensor with computeGrad == false";
                    initGraph();
                }
                return dcg;
            }
            tensor<T> gradient(){ return graph()->gradient; }
            void backward(){
                if (!isScalar()) throw "backward can only be called on a scalar tensor";
#ifdef DEBUG
                std::cout << "Calling backward on a scalar tensor" << std::endl;
#endif
                graph()->backward();
            }

    };
    
    template <typename T = float>
    inline tensor<T> make_scalar(const T& t, const bool& computeGrad = false);
    
    /***********************************************************************************
    *********************************** Aliases ****************************************
    ************************************************************************************/
    
    template<typename T>
    using Parameter = tensor<T>;
    template<typename T>
    using Parameters = std::vector<tensor<T>>;
    
    template<class T>
    using Variable = Tensor<T>; // A nice alias

    template<class T>
    using TensorFunction = Tensor<T>(*)(Tensor<T>&);

    
    template<typename T, template<typename> class MatrixType>
    std::ostream& operator<<(std::ostream& out, Tensor<T>& t){
        return out << t.data();
    }
    /*
        Since the operator<< has been overloaded for the shared_ptr to
        a Tensor type, to print the actual pointer, you must use the get() method
    */
    template<typename T, template<typename> class MatrixType>
    std::ostream& operator<<(std::ostream& out, tensor<T> t){
        if (t == nullptr){
            return out << "cml::tensor::nullptr";
        }
        out << "cml::tensor({";
        for (int i = 0; i<t->rows(); ++i){
            if (i > 0) out << "," << std::endl << "             ";

            out << "{";
            for (int j = 0; j<t->cols(); ++j){
                if (j > 0) out << ", ";
                out << t->coeff(i, j);
            }
            out << "}";
        }
        out << "}";
        if (t->computeGrad){
            out << ", computeGrad = true";
        }
        return out << ")";
    }
    


//     /***********************************************************************************
//     ********************************* Constructors *************************************
//     ************************************************************************************/

//     template <typename T, template <typename> class MatrixType>
//     Tensor<T, MatrixType>::Tensor(Tensor<T, MatrixType>&& t)
//         : MatrixType<T>{std::move(t.data())},
//           dcg{std::move(t.dcg)},
//           dimensions{std::move(t.dimensions)},
//           computeGrad{t.computeGrad} {}
//     template <typename T, template <typename> class MatrixType>
//     Tensor<T, MatrixType>::Tensor(MatrixType<T>& m) : MatrixType<T>{m}, dimensions{m} {}
//     template <typename T, template <typename> class MatrixType>
//     Tensor<T, MatrixType>::Tensor(MatrixType<T>&& m) : MatrixType<T>{std::move(m)}, dimensions{m} {}

//     template<typename T, template<typename> class MatrixType>
//     Tensor<T, MatrixType>::Tensor(tlist<T> data, const bool& computeGrad): 
//             MatrixType<T>{1, data.size()},
//             computeGrad{computeGrad} {
//         this->set(std::forward<tlist<T>>(data));
//         dimensions.setMatrix(this->data());
//     }
//     template<typename T, template<typename> class MatrixType>
//     Tensor<T, MatrixType>::Tensor(tlist<tlist<T>> data, const bool& computeGrad): 
//             MatrixType<T>{data.size(), data.begin()->size()},
//             computeGrad{computeGrad} {
//         this->set(std::forward<tlist<tlist<T>>>(data));
//         dimensions.setMatrix(this->data());
//     }
//     template<typename T, template<typename> class MatrixType> template<typename... Dims>
//     Tensor<T, MatrixType>::Tensor(const Dims&... dims, const bool& computeGrad): 
//             MatrixType<T>{std::forward<Dims>(dims)...}, computeGrad{computeGrad} {
//         dimensions.setMatrix(this->data());
//     }

//     /***********************************************************************************
//     *********************************** Methods ****************************************
//     ************************************************************************************/

//     template<typename T, template<typename> class MatrixType>
//     void Tensor<T, MatrixType>::set(tlist<T> data, const bool& transpose){
//         unsigned int i = 0;
//         if (transpose){
//             for (auto& e : data) {
//                 this->data()(i, 0) = e;
//                 ++i;
//             }
//         }
//         else{
//             for (auto& e : data){
//                 this->data()(0, i) = e;
//                 ++i;
//             }
//         }
//     }
//     template<typename T, template<typename> class MatrixType>
//     void Tensor<T, MatrixType>::set(tlist<tlist<T>> data){
//         unsigned int i, j;

//         i = 0;
//         for (auto& row : data){
//             j = 0;
//             for (auto& e : row){
//                 this->data()(i, j) = e;
//                 ++j;
//             }
//             ++i;
//         }
//     }

//     /***********************************************************************************
//     ****************************** Arithmetic Methods **********************************
//     ************************************************************************************/
    
//     template<typename T, template<typename> class MatrixType> 
//     tensor<T, MatrixType> operator*(const T& scalar, tensor<T, MatrixType> t){
//         return tensorScalarMultiply(scalar, t);
//     }
//     template<typename T, template<typename> class MatrixType> 
//     tensor<T, MatrixType> operator/(tensor<T, MatrixType> t, const T& scalar){
//         return tensorScalarDivide(t, scalar);
//     }

//     template<typename T, template<typename> class MatrixType> 
//     tensor<T, MatrixType> operator+(tensor<T, MatrixType> lhs, tensor<T, MatrixType> rhs){
//         return tensorAdd(lhs, rhs);
//     }
//     template<typename T, template<typename> class MatrixType> 
//     tensor<T, MatrixType> operator-(tensor<T, MatrixType> lhs, tensor<T, MatrixType> rhs){
//         return tensorSubtract(lhs, rhs);
//     }
//     template<typename T, template<typename> class MatrixType> 
//     tensor<T, MatrixType> operator*(tensor<T, MatrixType> lhs, tensor<T, MatrixType> rhs){
//         return tensorMultiply(lhs, rhs);
//     }
//     template<typename T, template<typename> class MatrixType> 
//     tensor<T, MatrixType> operator/(tensor<T, MatrixType> lhs, tensor<T, MatrixType> rhs){
//         return tensorDivide(lhs, rhs);
//     }

//     /***********************************************************************************
//     ********************************** Dynamic Graph ***********************************
//     ************************************************************************************/

//     template<typename T, template<typename> class MatrixType>
//     void Tensor<T, MatrixType>::initGraph(std::vector<tensor<T, MatrixType>> params, GradientFunction<T, MatrixType> f){
//         if (!dcg){
//             dcg = std::make_unique<DCG<T, MatrixType>>(this, std::forward<std::vector<tensor<T, MatrixType>>>(params),
//                                                        std::forward<GradientFunction<T, MatrixType>>(f));
//         }
//         else{
//             throw "Called initGraph when graph already exists";
//         }
//     }

//     template<typename T, template<typename> class MatrixType>
//     std::unique_ptr<DCG<T, MatrixType>>& Tensor<T, MatrixType>::graph(){
//         if (!dcg) {
//             if (!computeGrad) throw "Getting graph of tensor with computeGrad == false";
//             initGraph();
//         }
//         return dcg;
//     }
    
//     template<typename T, template<typename> class MatrixType>
//     void Tensor<T, MatrixType>::backward(){
//         if (!isScalar()) throw "backward can only be called on a scalar tensor";
// #ifdef DEBUG
//         std::cout << "Calling backward on a scalar tensor" << std::endl;
// #endif
//         graph()->backward();
//     }
    

}


#endif // __CML_TENSORS_TENSOR_H__
