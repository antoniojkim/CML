#ifndef __CML_TENSORS_TENSORDIMENSION_H__
#define __CML_TENSORS_TENSORDIMENSION_H__

#include <vector>
#include <initializer_list>


namespace cml {

    struct TensorDimension {
        std::vector<unsigned int> dims;
        
        TensorDimension(std::vector<unsigned int>& dims): dims{dims} {}
        TensorDimension(std::vector<unsigned int>&& dims): dims{dims} {}
        TensorDimension(std::initializer_list<unsigned int>& dims): dims{dims} {}
        TensorDimension(std::initializer_list<unsigned int>&& dims): dims{dims} {}

        bool operator==(const TensorDimension& other){
            return dims == other.dims;
        }
        bool operator!=(const TensorDimension& other){
            return dims != other.dims;
        }
        bool isScalar(){
            for (auto& d : dims){
                if (d > 1) {
                    return false;
                }
            }
            return true;
        }
        unsigned int size(){
            unsigned int s = 1;
            for (auto& d : dims){
                s *= d;
            }
            return s;
        }

    };

}

#endif // __CML_TENSORS_TENSORDIMENSION_H__
