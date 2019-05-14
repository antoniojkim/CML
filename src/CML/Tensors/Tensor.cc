
#include "../Tensor.h"
#include "../Dtypes.h"

using namespace cml;
using namespace Eigen;


/***********************************************************************************
********************************* Constructors *************************************
************************************************************************************/

template<typename T>
Tensor<T>::Tensor(const int& R): Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>{R, 1} {}
template<typename T>
Tensor<T>::Tensor(const int& R, const int& C): Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>{R, C} {}
// Tensor(const int& R, const int& C, const int& D);



/***********************************************************************************
*********************************** Methods ****************************************
************************************************************************************/

template<typename T>
std::ostream& operator<<(std::ostream& out, Tensor<T>& t){
    return out << static_cast<DMatrix<T>&>(t);
}



/***********************************************************************************
**************************** Template Instantiations *******************************
************************************************************************************/

INSTANTIATE_TEMPLATES(Tensor);

