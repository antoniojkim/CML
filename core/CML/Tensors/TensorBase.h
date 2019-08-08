#ifndef __CML_TENSORS_TENSORBASE_H__
#define __CML_TENSORS_TENSORBASE_H__

#include <ctime>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <memory>
#include <vector>

#include <Eigen/Core>
#include <unsupported/Eigen/CXX11/Tensor>

#include "TensorDecl.h"
#include "../../Utils/Exceptions.h"
#include "../../Utils/TypeName.h"

namespace cml {

    template <typename T>
    using DMatrix = Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>;  // Dynamic Matrix
    template <typename T>
    using RefMatrix = Eigen::Ref<DMatrix<T>>;  // Ref to Dynamic Matrix
    template <typename T>
    using DBlock = Eigen::Block<DMatrix<T>, Eigen::Dynamic, Eigen::Dynamic, false>;  // Dynamic Block
    template <typename T>
    using DArray = Eigen::Array<T, Eigen::Dynamic, Eigen::Dynamic>;  // Dynamic Array
    template<typename T>
    using MatrixMap = Eigen::Map<DMatrix<T>, 0, Eigen::Stride<0, 0> >;


    
    template<typename T>
    class TensorBase {
        
        public:
            bool computeGrad = false; // If true, creates dynamic graph on forward pass
        
        protected:
            std::unique_ptr<DCG<T>> dcg = nullptr;
        
            TensorBase(const bool& computeGrad) : computeGrad{computeGrad} {}

        public:
            /*
                Get Matrix representation of Tensor
            */
            virtual MatrixMap<T> matrix() = 0;
            virtual T* data() = 0;
            tensor<T> transpose(){ return transpose(this); }
            T& item() {
                if (this->isScalar()) return this->at(0);
                throw "Tensor::item:  Cannot get item from non scalar tensor";
            }

            /*
                Get coefficients of Tensor
            */
            virtual T& at(const int& d1) = 0;
            virtual T& at(const int& d1, const int& d2) = 0;
            virtual T& at(const int& d1, const int& d2, const int& d3) = 0;
            virtual T& at(const int& d1, const int& d2, const int& d3, const int& d4) = 0;

            inline T& operator()(const int& d1) { return this->at(d1); }
            inline T& operator()(const int& d1, const int& d2) { return this->at(d1, d2); }
            inline T& operator()(const int& d1, const int& d2, const int& d3) { return this->at(d1, d2, d3); }
            inline T& operator()(const int& d1, const int& d2, const int& d3, const int& d4) { return this->at(d1, d2, d3, d4); }


            virtual DBlock<T> block(const int& startCol, const int& numCols) = 0;
            virtual DBlock<T> block(const int& startRow, const int& startCol, const int& numRows, const int& numCols) = 0;
        
            virtual void fill(const T& coefficient) = 0;
            virtual void ones() = 0;
            virtual void zero() = 0;
            virtual void randomize(const unsigned int& seed) = 0;

            virtual tensor<T> constant(const T& s = 0, const bool& computeGrad = false) = 0;

        
            virtual std::vector<int> shape() = 0;
            virtual bool isScalar() = 0;
            virtual int size() = 0;
            virtual int numDims() = 0;

        
            void initGraph(std::vector<tensor<T>> params = {}, GradientFunction<T> f = nullptr);
            std::unique_ptr<DCG<T>>& graph();
            tensor<T>& gradient();
            void backward();            


            virtual tensor<T> abs() = 0;

            virtual void apply(T(*f)(const T& x)) = 0;
            virtual tensor<T> expr(T(*f)(const T& x)) = 0;

            virtual tensor<T> multiply(tensor<T> other) = 0;

            virtual tensor<T> softmax() = 0;

    };
        
    /***********************************************************************************
    *********************************** Aliases ****************************************
    ************************************************************************************/
    
    template<typename T>
    using Parameter = tensor<T>;
    template<typename T>
    using Parameters = std::vector<tensor<T>>;
    
    template<class T>
    using Variable = tensor<T>; // A nice alias


    /***********************************************************************************
    *********************************** Aliases ****************************************
    ************************************************************************************/


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


#endif // __CML_TENSORS_TENSORBASE_H__
