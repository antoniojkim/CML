#include "../DCG.h"
#include "../Dtypes.h"

using namespace std;
using namespace cml;


/***********************************************************************************
********************************* Constructors *************************************
************************************************************************************/

template<typename T>
DCG<T>::DCG(Tensor<T>* t, std::vector<tensor<T>> params, GradientFunction<T> f): 
    params{params}, f{f}, isLeaf{params.size() == 0 && f == nullptr},
    gradient{isLeaf ? make_tensor<T>(t->rows(), t->cols(), false) : nullptr} {}



/***********************************************************************************
*********************************** Methods ****************************************
************************************************************************************/


template<typename T>
void DCG<T>::accumulateGradient(const std::vector<tensor<T>>& gradients){
    for (auto& g : gradients){
        if (gradient->rows() != g->rows() || gradient->cols() != g->cols()){
            using namespace std;
            cerr << "Dims do not match in accumuateGradient" << endl;
            cerr << "    gradient.shape: {" << gradient->rows() << ", " << gradient->cols() << "}" << endl;
            cerr << "    g.shape: {" << g->rows() << ", " << g->cols() << "}" << endl;
            throw "Dims do not match in accumuateGradient";
        }
        gradient->data() += g->data();
    }
#ifdef DEBUG
    using namespace std;
    cout << "Accumulated Gradient" << endl;
#endif
}

template<typename T>
void DCG<T>::backward(std::vector<tensor<T>> x){
    if (isLeaf){
        accumulateGradient(x);
    }
    else if (f){
        auto gradients = f(params, x);
        if (params.size() != gradients.size()){
            throw "Number of Gradients does not match number of Parameters";
        }
        for (unsigned int i = 0; i<params.size(); ++i){
            if (params[i]->computeGrad){
                if (gradients[i] == nullptr){
                    throw "Null Gradient for parameter";
                }
                params[i]->graph()->backward({gradients[i]});
            }
        }
    }
}

/***********************************************************************************
**************************** Template Instantiations *******************************
************************************************************************************/

INSTANTIATE_CLASS_TEMPLATES(DCG);