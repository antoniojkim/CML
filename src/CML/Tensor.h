#ifndef __CML_TENSOR_H__
#define __CML_TENSOR_H__

#include <Eigen/Core>

namespace cml {
    
    template <class T>
    struct __Tensor__: public Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>{
        __Tensor__(const int& R, const int& C);
    };
    
//     struct DoubleTensor: public Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>{
//         DoubleTensor(const int& R, const int& C);
//     };
//     struct FloatTensor: public Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic>{
//         FloatTensor(const int& R, const int& C);
//     };
//     struct LongTensor: public Eigen::Matrix<long, Eigen::Dynamic, Eigen::Dynamic>{
//         LongTensor(const int& R, const int& C);
//     };
    
    template class __Tensor__<float>;
    typedef __Tensor__<float> Tensor;
    typedef __Tensor__<float> FloatTensor;
    
    template class __Tensor__<double>;
    typedef __Tensor__<float> DoubleTensor;
    
    template class __Tensor__<long>;
    typedef class __Tensor__<long> LongTensor;
    
//     template<class T>
//     std::ostream& operator<<(std::ostream& out, const cml::Tensor<T>& t);
    
}


#endif // __CML_TENSOR_H__
