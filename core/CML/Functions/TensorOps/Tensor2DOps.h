#ifndef __CML_FUNCTIONS_TENSOROPS_TENSOR2DOPS_H__
#define __CML_FUNCTIONS_TENSOROPS_TENSOR2DOPS_H__

#include "../../Tensors/Tensor2D.h"

namespace cml {
    
    /*
    Declarations for TensorOps
    */


    template<typename T, template<typename> class MatrixType> 
    tensor<T, MatrixType> tensorScalarMultiply(const T& scalar, tensor<T, MatrixType> t);
    template<typename T, template<typename> class MatrixType> 
    void tensorScalarMultiply(const T& scalar, tensor<T, MatrixType> t, tensor<T, MatrixType> out);
    template<typename T, template<typename> class MatrixType> 
    tensor<T, MatrixType> tensorScalarDivide(tensor<T, MatrixType> t, const T& scalar);
    template<typename T, template<typename> class MatrixType> 
    void tensorScalarDivide(tensor<T, MatrixType> t, const T& scalar, tensor<T, MatrixType> out);

    template<typename T, template<typename> class MatrixType> 
    tensor<T, MatrixType> tensorAdd(tensor<T, MatrixType> lhs, tensor<T, MatrixType> rhs);
    template<typename T, template<typename> class MatrixType> 
    void tensorAdd(tensor<T, MatrixType> lhs, tensor<T, MatrixType> rhs, tensor<T, MatrixType> out);
    template<typename T, template<typename> class MatrixType> 
    tensor<T, MatrixType> tensorSubtract(tensor<T, MatrixType> lhs, tensor<T, MatrixType> rhs);
    template<typename T, template<typename> class MatrixType> 
    void tensorSubtract(tensor<T, MatrixType> lhs, tensor<T, MatrixType> rhs, tensor<T, MatrixType> out);
    template<typename T, template<typename> class MatrixType> 
    tensor<T, MatrixType> tensorMultiply(tensor<T, MatrixType> lhs, tensor<T, MatrixType> rhs);
    template<typename T, template<typename> class MatrixType> 
    void tensorMultiply(tensor<T, MatrixType> lhs, tensor<T, MatrixType> rhs, tensor<T, MatrixType> out);
    template<typename T, template<typename> class MatrixType> 
    tensor<T, MatrixType> tensorDivide(tensor<T, MatrixType> lhs, tensor<T, MatrixType> rhs);
    template<typename T, template<typename> class MatrixType> 
    void tensorDivide(tensor<T, MatrixType> lhs, tensor<T, MatrixType> rhs, tensor<T, MatrixType> out);

    /*
    
    // template<typename T>
    // inline tensor<T> operator+(const T& scalar, Tensor<T>& t){ return t+scalar; }
    // template<typename T>
    // inline tensor<T> operator+(const T& scalar, tensor<T>& t){ return *t+scalar; }
    // template<typename T>
    // inline Tensor<T> operator-(const T& scalar, Tensor<T>& t){ return (t*-1)+scalar; }
    template<typename T>
    tensor<T> operator*(const T& scalar, tensor<T> t){
        auto u = make_tensor<T>(static_cast<DMatrix<T>>(
            t->data() * scalar
        ));
        u->computeGrad = t->computeGrad;
        if (u->computeGrad){
            u->initGraph([scalar](std::vector<tensor<T>>& params, std::vector<tensor<T>> output) -> std::vector<tensor<T>> {
                return {make_tensor<T>({scalar})};
            });
        }
        return u;
    }
    template<typename T>
    inline tensor<T> operator*(tensor<T> t, const T& scalar){ return scalar*t; }
    template<typename T>
    tensor<T> operator*(tensor<T> lhs, tensor<T> rhs){
        auto t = make_tensor<T>(static_cast<DMatrix<T>>(
            lhs->data() * rhs->data()
        ));
        t->computeGrad = lhs->computeGrad | rhs->computeGrad;
        if (t->computeGrad){            
            t->initGraph({lhs, rhs}, [](std::vector<tensor<T>>& params, std::vector<tensor<T>> output) -> std::vector<tensor<T>> {
#ifdef DEBUG
                using namespace std;
                cout << "Tensor Multiplication Backward" << endl;
#endif
                auto lhs = params.at(0);
                auto rhs = params.at(1);
                auto output_grad = output.at(0);
                tensor<T> lhs_grad = nullptr;
                tensor<T> rhs_grad = nullptr;

                if (lhs->computeGrad){
                    lhs_grad = make_tensor<T>(static_cast<DMatrix<T>>(
                        // TODO:  Check to see if order is correct
                        output_grad->data() * rhs->transpose()
                    ));
                }
                if (rhs->computeGrad){
                    rhs_grad = make_tensor<T>(static_cast<DMatrix<T>>(
                        // TODO:  Check to see if order is correct
                        lhs->transpose() * output_grad->data()
                    ));
                }

                return {lhs_grad, rhs_grad};
            });
        }
        return t;
    }
     */

}

#endif // __CML_FUNCTIONS_TENSOROPS_TENSOR2DOPS_H__
