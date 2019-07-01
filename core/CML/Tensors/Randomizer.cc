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
