#include "../Randomizer.h"
#include "../Dtypes.h"

#include <random>

using namespace std;
using namespace cml;

    
std::random_device rd;
std::mt19937 e2(rd());
std::normal_distribution<> gauss(0, 1);

template<typename T>
T Randomizer::Gaussian(const T& t){ return (T)gauss(e2); }

INSTANTIATE_FUNCTION_TEMPLATES(Randomizer::Gaussian);
