#ifndef __CML_TENSORS_TENSORIMPL_H__
#define __CML_TENSORS_TENSORIMPL_H__

#include "Tensor.h"

#include "Tensor/TensorConstructors.h"
#include "Tensor/MakeTensors.h"
#include "Tensor/TensorAccessors.h"
#include "Tensor/TensorModifiers.h"
#include "Tensor/TensorMembers.h"

/******************************************************************
 ********************* Other Tensor Functions *********************
 ******************************************************************/

template<typename T>
std::ostream& Tensor<T>::print(std::ostream& out){
    return print(out, d.get(), d.get()+S);
}

template<typename T>
std::ostream& operator<<(std::ostream& out, tensor<T> t){
    return out << t->matrix();
}

#endif // __CML_TENSORS_TENSORIMPL_H__
