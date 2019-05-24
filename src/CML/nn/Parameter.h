#ifndef __CML_NN_PARAMETER_H__
#define __CML_NN_PARAMETER_H__

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "../Tensor.h"

namespace cml {
namespace nn {
        
    template <typename T = float> class Parameter;
    template <typename T> using uParameter = std::unique_ptr<Parameter<T>>;

    template <typename T>
    class Parameter: public Tensor<T> {
        protected:
            bool requires_grad = true;

        public:
            Parameter(Parameter<T>& p);
            template<typename...Args> 
            Parameter(Args&&... args): cml::Tensor<T>(std::forward<Args>(args)...) {}

            template<class U> uParameter<U> to();

            cml::Tensor<T>& toTensor();
    };

    template<typename T>
    std::ostream& operator<<(std::ostream& out, Parameter<T>& p){
        return out << static_cast<cml::Tensor<T>&>(p);
    }


    template <typename T, typename...Args>
    inline uParameter<T> new_parameter(Args&&...args) {
        return std::unique_ptr<Parameter<T>>(new Parameter<T>(std::forward<Args>(args)...));
    }

    template<typename T>
    struct Parameters {
        std::vector<uParameter<T>> params;
        std::map<std::string, Parameter<T>*> values;

        void emplace_back(uParameter<T>&& p, const std::string& key = "");
        void push_back(uParameter<T>&& p, const std::string& key = "");
        void append(uParameter<T>&& p, const std::string& key = "");
        void add(uParameter<T>&& p, const std::string& key = "");

        Parameter<T>& operator[](const int& index);
        Parameter<T>& operator[](const std::string& key);
    };
    
}
}

#endif // __CML_NN_PARAMETER_H__
