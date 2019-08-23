#ifndef __EXCEPTIONS__

#include <exception>
#include <string>
#include <sstream>

#define CML_THROW(x) std::ostringstream err; err << x; throw err.str()

class UnimplementedException: public std::exception {
    
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

#endif // __EXCEPTIONS__
