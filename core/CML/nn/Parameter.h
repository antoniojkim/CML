#ifndef __CML_NN_PARAMETER_H__
#define __CML_NN_PARAMETER_H__

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "../Dtypes.h"
#include "../Tensor.h"

namespace cml {
namespace nn {
        
    template <typename T = float> class Parameter;
    template <typename T> using uParameter = std::unique_ptr<Parameter<T>>;

    /*
        A kind of Tensor that is to be considered a module parameter.

        It keeps track of which module Tensors require gradients
    */
    template <typename T>
    class Parameter: public Tensor<T> {
        bool requires_grad = true;
        tensor<T> gradient;

        public:
            /*
                If the argument is a reference to a parameter class, it will 
                construct the parameter by moving the data of the passed in parameter
                object.

                Note that the template type of the argument can be any supported type
                as it will automatically type cast it into type T.
            */
            template<typename U>
            Parameter(Parameter<U>& p): cml::Tensor<T>(p.toTensor()), 
                                        gradient{make_tensor<T>(DMatrix<T>::Zero(this->rows(), this->cols()))} {}
            /*
                In all other cases, it will construct the parameter object by
                perfect forwarding all of the passed in arguments.
            */
            template<typename...Args, DisableIf<is_related<Parameter<T>, Args...>::value>...> 
            Parameter(Args&&... args): cml::Tensor<T>(std::forward<Args>(args)...),
                                       gradient{make_tensor<T>(DMatrix<T>::Zero(this->rows(), this->cols()))} {}


            /*
                Casts the parameter value to the provided template type.
                Note that this moves the data from the Tensor. 
                A new instance of parameter is returned with the moved, casted data
                as C++ is statically typed and the type of the current instance
                cannot be changed.
            */
            template<class U> Parameter<U> to(){ return Parameter<U>(*this); }

            /*
                Adds to the parameter's gradient
            */
            Parameter<T>& operator+=(tensor<T>);
            /*
                Zeros out the gradient. Useful as gradients are accumulated.
            */
            void zeroGrad();

            /*
                Gets the parameter Tensor data
            */
            cml::Tensor<T>& toTensor();
    };

    template<typename T>
    std::ostream& operator<<(std::ostream& out, Parameter<T>& p){
        return out << p.toTensor();
    }

    /*
        This method serves as an easy and convenient way to construct a unique
        pointer of type Parameter<T>
    */
    template <typename T, typename...Args>
    inline uParameter<T> new_parameter(Args&&...args) {
        return std::unique_ptr<Parameter<T>>(new Parameter<T>(std::forward<Args>(args)...));
    }


    /*
        This structure serves as an easy way to store and access multiple parameters
    */
    template<typename T>
    struct Parameters {
        std::vector<uParameter<T>> params;
        /*
            Stores the mapping between parameter aliases and its respective parameter
        */
        std::map<std::string, Parameter<T>*> values;

        /*
            The following methods allow you to add a submodule to your module.
            Multiple aliases are declared for ease of use, but they all perform 
            the same action.
        */
        void emplace_back(uParameter<T>&& p, const std::string& key = "");
        void push_back(uParameter<T>&& p, const std::string& key = "");
        void append(uParameter<T>&& p, const std::string& key = "");
        void add(uParameter<T>&& p, const std::string& key = "");

        /*
            The following method can be used to get the invidual parameters
            in the order that they were added. i.e., the first parameter added
            would be at index 0.

            In addition, negative indexing is supported. i.e., the last parameter
            added would be at index -1.

            Note that generally, the order of parameters is not usually known.
            So, this method should be used with caution.
        */
        Parameter<T>& operator[](const int& index);
        /*
            The following method can be used to get the individual parameters
            using the alias that was provided when it was added.

            The aliases will generally be specified in the documentation for
            that specific module.
            
            Since the order in which the paramters is not usually known, this
            is the recommended way to access individual parameters.
        */
        Parameter<T>& operator[](const std::string& key);
    };
    
}
}

#endif // __CML_NN_PARAMETER_H__
