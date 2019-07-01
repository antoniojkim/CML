#ifndef __CML_UTILS_DATASOURCE_H__
#define __CML_UTILS_DATASOURCE_H__

#include <iostream>
#include <fstream>
#include <string>
#include <Eigen/Core>

#include "DataFormats/idx.h"

namespace cml {
    
    enum DataFormat {
        NONE,
        IDX
    };
    
    template<typename T>
    struct DataSource {
        DataFormat format;
        std::ifstream file;
        DMatrix<T> data;
        
        DataSource(const DataFormat& format, const std::string& path): 
            format{format}, file{path, std::ios::in | std::ios::binary}, data{0, 0} {
            switch (format){
                case DataFormat::IDX:
                    idx::read(file, data);
                    break;
                default:
                    throw "Invalid DataFormat";
            }
        }
        
    };
        
    
}

#endif // __CML_UTILS_DATASOURCE_H__
