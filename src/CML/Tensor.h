#ifndef __CML_TENSOR_H__
#define __CML_TENSOR_H__

#include <Eigen/Core>

namespace cml {
    
    template <class T>
    struct __Tensor__: public Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>{
        __Tensor__(const int& R);
        __Tensor__(const int& R, const int& C);
        // __Tensor__(const int& R, const int& C, const int& D);
    };
    
    template class __Tensor__<float>;
    typedef __Tensor__<float> Tensor;
    typedef __Tensor__<float> FloatTensor;
    
    template class __Tensor__<double>;
    typedef __Tensor__<double> DoubleTensor;
    
    template class __Tensor__<long>;
    typedef class __Tensor__<long> LongTensor;


    
}


#endif // __CML_TENSOR_H__
