#ifndef __CML_UTILS_DATAREADER_H__
#define __CML_UTILS_DATAREADER_H__

#include <iostream>
#include <fstream>
#include <string>

#include "../CML/Tensor.h"
#include "DataFormats/idx.h"

namespace cml {

    enum DataFormat {
        INVALID,
        IDX
    };

    template<typename T, template<typename> class TensorType>
    struct DataReader {
        DataFormat format;

        DataReader(const DataFormat& format): format{format} {}

        tensor<T> load(const std::string& path){
            std::ifstream file {path, std::ios::in | std::ios::binary};

            switch (format){
                case DataFormat::IDX:
                    return idx::read<T, TensorType>(file);
                default:
                    throw "Invalid DataFormat";
            }
        }

    };


}

#endif // __CML_UTILS_DATAREADER_H__
