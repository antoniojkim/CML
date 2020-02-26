#pragma once

#include <exception>
#include <string>
#include <sstream>

namespace numeric {

    struct Exception: std::exception {

        std::string msg;
        
        template<typename...Args>
        Exception(Args&&... args){
            std::ostringstream oss;
            (oss << ... << args);
            msg = oss.str();
        }

        virtual const char * what () const throw (){
            return msg.c_str();
        }

    };

}
