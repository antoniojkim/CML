#ifndef __CML_NN_PARAMETER_H__
#define __CML_NN_PARAMETER_H__

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "../Tensor.h"

namespace cml {
namespace nn {
    
    template <class T = float> class __parameter__;
    class parameter;

    typedef parameter* Parameter;
    typedef std::unique_ptr<parameter> uParameter;

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

            virtual std::ostream& print(std::ostream& out) = 0;

            friend std::ostream& operator<<(std::ostream& out, Parameter p){
                return p->print(out);
            }
    };

    template <class T>
    class __parameter__: public parameter, public __Tensor__<T> {

        public:
            // template<typename...Args>
            // __parameter__(Args... args): __Tensor__<T>(std::forward<Args>(args)...) {}
            template<typename...Args>
            __parameter__(const int& R, const int& C): __Tensor__<T>(R, C) {}
            template <class U>
            __parameter__(__parameter__<U>&& p): __Tensor__<T>(p) {}
            // ~__parameter__() override {}

            std::ostream& print(std::ostream& out){
                return out << dynamic_cast<__Tensor__<T>*>(this);
            }
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

    struct Parameters {
        std::vector<uParameter> params;
        std::map<std::string, Parameter> values;

        void emplace_back(uParameter&&, const std::string& key = "");
        void push_back(uParameter&&, const std::string& key = "");
        void append(uParameter&&, const std::string& key = "");
        void add(uParameter&&, const std::string& key = "");

        Parameter operator[](const int& index);
        Parameter operator[](const std::string& key);
    };
    
}
}

#endif // __CML_NN_PARAMETER_H__
