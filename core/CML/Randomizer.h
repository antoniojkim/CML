#ifndef __CML_RANDOMIZER_H__
#define __CML_RANDOMIZER_H__

#include <functional>

namespace cml {
namespace Randomizer {
    
    template<typename T>
    using Function = std::function<T(const T&)>;
    
    template<typename T>
    T Gaussian(const T& t);
    
} 
}

#endif // __CML_RANDOMIZER_H__
