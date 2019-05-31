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
        DCG<T>* graph = nullptr;

        public:
            template<typename U>
            Tensor(Tensor<U>& t): DMatrix<T>{std::move(t.data().template cast<T>())} {}
            template<typename U>
            Tensor(Tensor<U>&& t): DMatrix<T>{std::move(t.data().template cast<T>())} {}
            template<typename U>
            Tensor(DMatrix<U>& m): DMatrix<T>{std::move(m.template cast<T>())} {}
            template<typename U>
            Tensor(DMatrix<U>&& m): DMatrix<T>{std::move(m.template cast<T>())} {}
            Tensor(const int& R);
            Tensor(const int& R, const int& C);
            // Tensor(const int& R, const int& C, const int& D);

            DMatrix<T>& data();

            Tensor<T> operator*(const long long& scalar);
    };

    template<typename T>
    inline Tensor<T> operator*(const long long& scalar, Tensor<T>& t){ return t*scalar; }
    
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
