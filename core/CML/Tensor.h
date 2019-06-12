#ifndef __CML_TENSOR_H__
#define __CML_TENSOR_H__

#include <Eigen/Core>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <memory>
#include <vector>

#include "Randomizer.h"

namespace cml {

    template <class T = float> struct Tensor;
    template <class T = float> struct DCG; // Dynamic Compute Graph

    /*
        Note that the lower case tensor is used for a shared_ptr to a Tensor object.
        Lowercase as it isn't a direct reference, but rather an indirect one.
    */
    template<class T>
    using tensor = std::shared_ptr<Tensor<T>>;

    /*
        This is the recommended way to construct a matrix
    */
    template<class T = float, typename... Args>
    inline tensor<T> make_tensor(Args&&... args){
        return std::make_shared<Tensor<T>>(std::forward<Args>(args)...);
    }
    template<class T = float>
    inline tensor<T> make_tensor(std::initializer_list<T> data, const bool& computeGrad = false){
        return std::make_shared<Tensor<T>>(data, computeGrad);
    }
    template<class T = float>
    inline tensor<T> make_tensor(std::initializer_list<std::initializer_list<T>> data, const bool& computeGrad = false){
        return std::make_shared<Tensor<T>>(data, computeGrad);
    }

    template<typename T>
    using DMatrix = Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>; // Dynamic Matrix
    
    template <class T>
    class Tensor: public DMatrix<T>{
        
        std::unique_ptr<DCG<T>> dcg = nullptr;

        public:
            bool computeGrad = false; // If true, creates dynamic graph on forward pass

            // Tensor(tensor<T> t);
            // Tensor(Tensor<T>& t);
            Tensor(Tensor<T>&& t);
            Tensor(DMatrix<T>& m);
            Tensor(DMatrix<T>&& m);
            Tensor(std::initializer_list<T> data, const bool& computeGrad = false);
            Tensor(std::initializer_list<std::initializer_list<T>> data, const bool& computeGrad = false);
            Tensor(const int& R, const int& C = 1, const bool& computeGrad = false);

            /*
                Constructors that cast the input if type is not T
            */
            template<typename U>
            Tensor(Tensor<U>& t): Tensor{std::move(t.data().template cast<T>())} {}
            template<typename U>
            Tensor(Tensor<U>&& t): Tensor{std::move(t.data().template cast<T>())} {}
            template<typename U>
            Tensor(DMatrix<U>& m): Tensor{std::move(m.template cast<T>())} {}
            template<typename U>
            Tensor(DMatrix<U>&& m): Tensor{std::move(m.template cast<T>())} {}

            ~Tensor() = default;

            // Tensor<T>& operator=(Tensor<T>& scalar);
            // Tensor<T>& operator=(Tensor<T>&& scalar);

            DMatrix<T>& data();
            T& data(const int& R, const int& C);
            std::vector<long int> shape();
            std::ostream& info(std::ostream& out = std::cout);

            void fill(const T& coefficient);
            void zero();
            void randomize(Randomizer::Function<T> randomizer = Randomizer::Gaussian<T>);
            void randomize(const T& coefficient);

            /*
                Read values in using the IDX format
            */
            void readIDX(std::istream& in, const bool& readMagic = true);
        

            void initGraph(std::function<void(tensor<T>)> f);
            std::unique_ptr<DCG<T>>& graph();
            void backward();
            
    };

    
    template<typename T>
    std::ostream& operator<<(std::ostream& out, Tensor<T>& t){
        return out << t.data();
    }
    /*
        Since the operator<< has been overloaded for the shared_ptr to
        a Tensor type, to print the actual pointer, you must use the get() method
    */
    template<typename T>
    std::ostream& operator<<(std::ostream& out, tensor<T> t){
        out << "cml::tensor({";
        // t->info(out) << " [";
        out << t->data() << "}";
        if (t->computeGrad){
            out << ", computeGrad = true";
        }
        return out << ")";
    }
    
    template<class T>
    using Variable = Tensor<T>; // A nice alias

    template<class T>
    using TensorFunction = Tensor<T>(*)(Tensor<T>&);



    /***********************************************************************************
    ****************************** Arithmetic Methods **********************************
    ************************************************************************************/


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
            u->initGraph([scalar, t](tensor<T> output) -> void {
                t->graph()->accumulateGradient(scalar);
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
            t->initGraph([lhs, rhs](tensor<T> output) -> void {
                if (lhs->computeGrad){
                    auto gradient = rhs * output;
                    if (lhs->graph()->isLeaf){
                        lhs->graph()->accumulateGradient(gradient);
                    }
                    else{
                        lhs->graph()->backward(gradient);
                    }
                }
                if (rhs->computeGrad){
                    auto gradient = lhs * output;
                    if (rhs->graph()->isLeaf){
                        rhs->graph()->accumulateGradient(gradient);
                    }
                    else{
                        rhs->graph()->backward(gradient);
                    }
                }
            });
            t->graph()->isLeaf = false;
        }
        return t;
    }
    

}


#endif // __CML_TENSOR_H__
