#ifndef __CML_TENSOR_H__
#define __CML_TENSOR_H__

#include <Eigen/Core>

namespace cml {

    template<typename T>
    using DMatrix = Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>; // Dynamic Matrix
    
    template <class T = float>
    struct Tensor: public DMatrix<T>{
        Tensor(const int& R);
        Tensor(const int& R, const int& C);
        // Tensor(const int& R, const int& C, const int& D);

    };
    
    template<typename T>
    std::ostream& operator<<(std::ostream& out, Tensor<T>& t);
    
}


#endif // __CML_TENSOR_H__
