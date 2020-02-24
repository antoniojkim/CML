#pragma once

#include <string>
#include <sstream>

namespace numeric {

    struct Exception {

        std::string msg;
        
        template<typename...Args>
        Exception(Args&&... args){
            std::ostringstream oss;
            for (auto& arg: {args...}){
                oss << arg;
            }
            msg = oss.str();
        }

        virtual const char * what () const throw (){
            return msg.c_str();
        }

    };

}
