
#include "../Parameter.h"

using namespace std;
using namespace cml::nn;

parameter::parameter(const bool& requires_grad): requires_grad{requires_grad} {}


void Parameters::emplace_back(uParameter&& p, const std::string& key){ add(std::move(p), key); }
void Parameters::push_back(uParameter&& p, const std::string& key){ add(std::move(p), key); }
void Parameters::append(uParameter&& p, const std::string& key){ add(std::move(p), key); }
void Parameters::add(uParameter&& p, const std::string& key){
    params.emplace_back(std::move(p));
    if (key != ""){
        values[key] = params.back().get();
    }
}


Parameter Parameters::operator[](const int& index){
    if (index >= 0 && index < (int) params.size()){
        return params[index].get();
    }
    else if (index < 0 && -index <= (int) params.size()){
        return params[params.size()+index].get();
    }
    ostringstream error;
    error << "Invalid index: " << index << ",  params.size() == " << params.size() << endl;
    throw error.str();
}
Parameter Parameters::operator[](const std::string& key){
    if (values.count(key) > 0){
        return values[key];
    }
    
    ostringstream error;
    error << "Invalid key: " << key;
    throw error.str();
}
