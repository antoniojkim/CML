#ifndef __CML_TENSOR_H__
#define __CML_TENSOR_H__

#include <Eigen/Core>

namespace cml {

    template <class T = float> struct Tensor;

    template<typename T>
    using DMatrix = Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>; // Dynamic Matrix
    
    template <class T>
    struct Tensor: public DMatrix<T>{
        template<typename U>
        Tensor(Tensor<U>& t): DMatrix<T>{std::move(t.data().template cast<T>())} {}
        Tensor(const int& R);
        Tensor(const int& R, const int& C);
        // Tensor(const int& R, const int& C, const int& D);

        DMatrix<T>& data();
    };
    
    template<typename T>
    std::ostream& operator<<(std::ostream& out, Tensor<T>& t){
        return out << t.data();
    }
    
}


#endif // __CML_TENSOR_H__
