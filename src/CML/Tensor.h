#ifndef __CML_TENSOR_H__
#define __CML_TENSOR_H__

#include <Eigen/Core>

namespace cml {


    template <class T = float> struct Tensor;
    template <class T = float> struct DCG; // Dynamic Compute Graph

    template<typename T>
    using DMatrix = Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>; // Dynamic Matrix
    
    template <class T>
    class Tensor: public DMatrix<T>{
        const long int R, C;

        public:

            Tensor(Tensor<T>& t);
            Tensor(Tensor<T>&& t);
            Tensor(DMatrix<T>& m);
            Tensor(DMatrix<T>&& m);
            Tensor(const int& R);
            Tensor(const int& R, const int& C);
            // Tensor(const int& R, const int& C, const int& D);

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

            ~Tensor();

            Tensor<T>& operator=(Tensor<T>& scalar);
            Tensor<T>& operator=(Tensor<T>&& scalar);

            DMatrix<T>& data();
            long int rows();
            long int cols();

            void fill(const T& coefficient);
            void zero();
            void randomize();
            void randomize(const T& coefficient);

            // Tensor<T> operator+(const T& scalar);
            // Tensor<T> operator-(const T& scalar);
            Tensor<T> operator*(const T& scalar);
            
            DCG<T>* graph = nullptr;
    };

    template<typename T>
    inline Tensor<T> operator+(const T& scalar, Tensor<T>& t){ return t+scalar; }
    // template<typename T>
    // inline Tensor<T> operator-(const T& scalar, Tensor<T>& t){ return (t*-1)+scalar; }
    template<typename T>
    inline Tensor<T> operator*(const T& scalar, Tensor<T>& t){ return t*scalar; }
    
    template<typename T>
    std::ostream& operator<<(std::ostream& out, Tensor<T>& t){
        return out << t.data();
    }
    
    template<class T>
    using Variable = Tensor<T>; // A nice alias

    template<class T>
    using TensorFunction = Tensor<T>(*)(Tensor<T>&);

}


#endif // __CML_TENSOR_H__
