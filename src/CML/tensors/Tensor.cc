
#include "../Tensor.h"

using namespace cml;
using namespace Eigen;

template<class T>
__Tensor__<T>::__Tensor__(const int& R, const int& C): Matrix<T, Dynamic, Dynamic>{R, C} {}

// FloatTensor::FloatTensor(const int& R, const int& C): Matrix<float, Dynamic, Dynamic>{R, C} {}

// LongTensor::LongTensor(const int& R, const int& C): Matrix<long, Dynamic, Dynamic>{R, C} {}


// std::ostream& operator<<(std::ostream& out, const Tensor& t){
//     return out << t;
// }
