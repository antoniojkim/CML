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
    
    std::string exceptionName;
    std::ostringstream err;
    
    template<typename... Args>
    CMLException(Args&&... args) {
        PrintVariadic<Args...>::print(err, std::forward<Args>(args)...);
    }

    void setExceptionName(const std::string& s){ exceptionName = s; }
    
    const char* what() const throw() override {
        return std::runtime_error(exceptionName + err.str()).what();
    }
};

#define CML_THROW(x) throw CMLException(x);

struct UnimplementedException: public CMLException {

    template<typename... Args>
    UnimplementedException(Args&&... args): CMLException(std::forward<Args>(args)...) {
        setExceptionName("UnimplementedException: ");
    }
};

struct TensorTypeMismatchException: public CMLException {

    template<typename... Args>
    TensorTypeMismatchException(Args&&... args): CMLException(std::forward<Args>(args)...) {
        setExceptionName("Tensor Type Mismatch Exception: ");
    }
};

struct UnsupportedOperationException: public CMLException {

    template<typename... Args>
    UnsupportedOperationException(Args&&... args): CMLException(std::forward<Args>(args)...) {
        setExceptionName("UnsupportedOperationException: ");
    }
};

struct InvalidDimensionException: public CMLException {

    template<typename... Args>
    InvalidDimensionException(Args&&... args): CMLException(std::forward<Args>(args)...) {
        setExceptionName("InvalidDimensionException: ");
    }
};

struct AssertionFailedException: public CMLException {

    template<typename... Args>
    AssertionFailedException(Args&&... args): CMLException(std::forward<Args>(args)...) {
        setExceptionName("AssertionFailedException: ");
    }
};

#endif // __CML_UTILS_EXCEPTIONS_H__
