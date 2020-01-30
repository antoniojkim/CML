#ifndef __CML_TENSORS_TENSORIMPL_H__
#define __CML_TENSORS_TENSORIMPL_H__

#include "Tensor.h"

#include "TensorConstructors.h"
#include "MakeTensors.h"
#include "TensorAccessors.h"
#include "TensorModifiers.h"
#include "TensorMembers.h"

/******************************************************************
 ********************* Other Tensor Functions *********************
 ******************************************************************/

namespace cml {

    template<typename T>
    std::ostream& Tensor<T>::print(std::ostream& out){
        return cml::print(out, d.get(), d.get()+S);
    }

    template<typename T>
    std::ostream& operator<<(std::ostream& out, tensor<T> t){
        return out << t->matrix();
    }

}

#endif // __CML_TENSORS_TENSORIMPL_H__
