#ifndef __CML_UTILS_RANDOM_H__
#define __CML_UTILS_RANDOM_H__

#include <chrono>
#include <random>

namespace cml {
namespace Random {

    template<typename T>
    using Function = T(*)(const T& t);

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator (seed);
    std::normal_distribution<double> gauss_dist (0.0,1.0);

    template<typename T>
    inline T Gaussian(const T& t){ return (T)gauss_dist(generator); }

    inline Eigen::VectorXi eigenMatrixRandomizer(const int& size){
        Eigen::VectorXi indices = Eigen::VectorXi::LinSpaced(size, 0, size);
        std::random_shuffle(indices.data(), indices.data() + size);
        return indices;
    }

}
}

#endif // __CML_UTILS_RANDOM_H__
