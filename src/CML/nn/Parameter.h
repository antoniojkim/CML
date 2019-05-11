#ifndef __CML_NN_PARAMETER_H__
#define __CML_NN_PARAMETER_H__

#include <memory>
#include <vector>

#include "../Tensor.h"

namespace cml {
namespace nn {
    
    template <class T = float> class __parameter__;
    class parameter;

    typedef parameter* Parameter;
    typedef std::unique_ptr<parameter> uParameter;
    typedef std::vector<uParameter> Parameters;

    class parameter {
        protected:
            bool requires_grad = true;

        public:
            parameter(const bool& requires_grad = true);
            // virtual ~parameter() = 0;

            template<class U>
            Parameter to(){
                return std::make_unique<__parameter__<U>>(std::move(*this));
            }
    };

    template <class T>
    class __parameter__: public parameter, public __Tensor__<T> {

        public:
            // template<typename...Args>
            // __parameter__(Args... args): __Tensor__<T>(args...) {}
            template<typename...Args>
            __parameter__(const int& R, const int& C): __Tensor__<T>(R, C) {}
            template <class U>
            __parameter__(__parameter__<U>&& p): __Tensor__<T>(p) {}
            // ~__parameter__() override {}
    };

    template class __parameter__<float>;
    template class __parameter__<double>;
    template class __parameter__<long>;


    // template <typename T, typename...Args>
    // inline Parameter new_parameter(Args&&...args) {
    //     return std::unique_ptr<__parameter__<T>>(std::forward<Args>(args)...);
    // }
    template <typename T>
    inline uParameter new_parameter(const int& R, const int& C) {
        return std::make_unique<__parameter__<T>>(R, C);
    }
    
}
}

#endif // __CML_NN_PARAMETER_H__
