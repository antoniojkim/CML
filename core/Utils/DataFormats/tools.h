#ifndef __CML_UTILS_DATAFORMATS_TOOLS_H__
#define __CML_UTILS_DATAFORMATS_TOOLS_H__

#include <Eigen/Core>

template<typename T>
using DMatrix = Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>; // Dynamic Matrix

#endif // __CML_UTILS_DATAFORMATS_TOOLS_H__
