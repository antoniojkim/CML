#ifndef __CML_UTILS_EXCEPTIONS_H__
#define __CML_UTILS_EXCEPTIONS_H__

#include <exception>
#include <string>
#include <sstream>
#include <ostream>

#include "VectorUtils.h"

template<typename... Args>
struct PrintVariadic;

template<typename T, typename... Args>
struct PrintVariadic<T, Args...>{
    static void print(std::ostream& out, const T& t, Args&&... args){
        out << t << " ";
        PrintVariadic<Args...>::print(out, std::forward<Args>(args)...);
    }
};

template<>
struct PrintVariadic<>{
    static void print(std::ostream& out){}
};


struct CMLException: public std::exception {
    
    std::ostringstream err;
    
    template<typename... Args>
    CMLException(Args&&... args) {
        PrintVariadic<Args...>::print(err, std::forward<Args>(args)...);
    }
    
    const char* what() const throw() override {
        return std::runtime_error(err.str()).what();
    }
};

#define CML_THROW(x) throw CMLException(x);

class UnimplementedException: public std::exception {
    
    std::string message;
    
    public:
        UnimplementedException(const std::string& message): message{message} {}
    
    private:
        const char* what() const throw() {            
            return (std::string("Unimplemented Exception:  ") + message).c_str();
        }
};

class TensorTypeMismatchException: public std::exception {
    const char* what() const throw() {            
        return "Tensor Type Mismatch Exception";
    }
};

class UnsupportedOperationException: public std::exception {
    
    std::string message;
    
    public:
        UnsupportedOperationException(const std::string& message): message{message} {}
    
    private:
        const char* what() const throw() {            
            return (std::string("Unsupported Operation Exception:  ") + message).c_str();
        }
};

class InvalidDimensionException: public std::exception {
    
    std::string message;
    
    public:
        InvalidDimensionException(const std::string& message): message{message} {}
    
    private:
        const char* what() const throw() {            
            return (std::string("Invalid Dimension Exception:  ") + message).c_str();
        }
};

#endif // __CML_UTILS_EXCEPTIONS_H__
