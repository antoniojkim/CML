#pragma once

#include <cstdlib>
#include <cstdint>
#include <iterator>
#include <memory>
#include <vector>

#include "array.h"
#include "dtypes.h"

namespace numeric {
    
    struct array_attributes {
        std::vector<std::size_t> shape;
        std::size_t size;
        Dtype dtype;
        std::size_t dtypesize;

        std::shared_ptr<void> data = nullptr;

        array_attributes(Dtype dtype);
        array_attributes(const std::vector<std::size_t>& shape, Dtype dtype);
        // array_attributes(std::initializer_list<std::size_t> shape, Dtype dtype);
    };

}
