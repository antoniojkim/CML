#ifndef __CML_TENSORS_TENSORDIMENSION_H__
#define __CML_TENSORS_TENSORDIMENSION_H__

#include <vector>
#include <initializer_list>


namespace cml {

    struct TensorDimension {
        std::vector<int> dims;
        
        TensorDimension(std::vector<int> dims): dims{dims} {}
        TensorDimension(std::initializer_list<int> dims): dims{dims} {}

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
        int size(){
            int s = 1;
            for (auto& d : dims){
                s *= d;
            }
            return s;
        }

    };

    std::ostream& operator<<(std::ostream& out, TensorDimension& dims){
        out << "{";
        bool first = true;
        for (auto& d : dims.dims){
            if (first){
                out << " " << d;
            }
            else{
                out << ", " << d;
                first = false;
            }
        }
        return out;
    }

}

#endif // __CML_TENSORS_TENSORDIMENSION_H__
