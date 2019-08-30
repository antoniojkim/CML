#ifndef __CML_UTILS_EXCEPTIONS_H__
#define __CML_UTILS_EXCEPTIONS_H__

#include <exception>
#include <string>
#include <sstream>

#include "VectorUtils.h"

struct CMLException: public std::exception {
    
    std::string exceptionName = "";
    std::ostringstream err;
    
    template<typename T>
    CMLException(const T& t) {
        err << t << " ";
    }
    template<typename T, typename... Args>
    CMLException(const T& t, Args&&... rest) {
        err << t << " ";
        CMLException(std::forward<Args>(rest)...);
    }
    
    const char* what() const throw() {            
        return (exceptionName + err.str()).c_str();
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
