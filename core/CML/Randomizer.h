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

/*
#include <chrono>

#include "../Randomizer.h"
#include "../Dtypes.h"

#include <random>

using namespace std;
using namespace cml;


unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
std::default_random_engine generator (seed);
std::normal_distribution<double> gauss_dist (0.0,1.0);

template<typename T>
T Randomizer::Gaussian(const T& t){ return (T)gauss_dist(generator); }

INSTANTIATE_FUNCTION_TEMPLATES(Randomizer::Gaussian);

 */

#endif // __CML_RANDOMIZER_H__
