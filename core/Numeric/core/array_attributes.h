#pragma once

#include <cstdlib>
#include <cstdint>
#include <iterator>
#include <memory>
#include <vector>

#include "array.h"
#include "dtypes.h"

namespace numeric {
    
    template<typename T>
    struct array_attributes {
        std::vector<std::size_t> shape {0};
        std::size_t size = 0;
        
        constexpr static Dtype dtype = TYPE_TO_DTYPE<T>();
        constexpr static std::size_t dtypesize = sizeof(T);

        std::shared_ptr<T[]> data = nullptr;

        array_attributes();
        array_attributes(const std::vector<std::size_t>& shape);
        array_attributes(const array_attributes<T>& other);
        array_attributes(array_attributes<T>&& other);
    };

}
