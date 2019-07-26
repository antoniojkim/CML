#ifndef __EXCEPTIONS__

#include <exception>
#include <string>

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

#endif // __EXCEPTIONS__
