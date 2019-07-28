#ifndef __CML_TENSORS_TENSORDIMENSION_H__
#define __CML_TENSORS_TENSORDIMENSION_H__

#include <vector>
#include <initializer_list>


namespace cml {

    struct TensorDimension {
        std::vector<int> dims;
        
        TensorDimension(std::vector<int>& dims): dims{dims} {}
        TensorDimension(std::initializer_list<int> dims): dims{dims} {}

        bool operator==(const TensorDimension& other){
            return dims == other.dims;
        }
        bool operator!=(const TensorDimension& other){
            return dims != other.dims;
        }
        int operator[](const int& i){
            if (i >= int(dims.size()) || i < -int(dims.size())){
                throw "TensorDimension:: Invalid index";
            }
            if (i >= 0){
                return dims[i];
            }
            else {
                return dims[dims.size()+i];
            }
        }
        bool isScalar(){
            for (auto& d : dims){
                if (d > 1) {
                    return false;
                }
            }
            return true;
        }
        int numBatches(){
            return dims[0];
        }
        int size(){
            int s = 0;
            for (auto& d : dims){
                if (s == 0){
                    s = 1;
                }
                else{
                    s *= d;
                }
            }
            return s;
        }

        static int numBatches(std::vector<int>& dims){
            return dims[0];
        }
        static int size(std::vector<int>& dims){
            int s = 0;
            for (auto& d : dims){
                if (s == 0){
                    s = 1;
                }
                else{
                    s *= d;
                }
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
        out << " }";
        return out;
    }

}

#endif // __CML_TENSORS_TENSORDIMENSION_H__
