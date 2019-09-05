#ifndef __CML_FUNCTIONS_TENSOROPS_TENSORADDMULTIPLY_H__
#define __CML_FUNCTIONS_TENSOROPS_TENSORADDMULTIPLY_H__

#include "TensorOps.h"

namespace cml {

    template<typename T>
    std::vector<tensor<T>> addmatmul_backwards(std::vector<tensor<T>>& params, std::vector<tensor<T>> output) {
            tensor<T> t1 = params.at(0);
        tensor<T> t2 = params.at(1);
        tensor<T> t3 = params.at(2);
        tensor<T> output_grad = output.at(0);
        tensor<T> t1_grad = nullptr;
        tensor<T> t2_grad = nullptr;
        tensor<T> t3_grad = nullptr;
#ifdef DEBUG
        using namespace std;
        cout << "Tensor2D Add Matrix Multiply Backward" << endl;
        cout << "    t1: " << t1->rows() << ", " << t1->cols() << "   computeGrad: " << t1->computeGrad << endl;
        cout << "    t2: " << t2->rows() << ", " << t2->cols() << "   computeGrad: " << t2->computeGrad << endl;
        cout << "    t3: " << t3->rows() << ", " << t3->cols() << "   computeGrad: " << t3->computeGrad << endl;
        cout << "    output_grad: " << output_grad->rows() << ", " << output_grad->cols() << endl;
#endif

        if (t3->computeGrad){
            t3_grad = make_tensor<T>(static_cast<DMatrix<T>>(
                // TODO:  Check to see if order is correct
                t2->matrix().transpose() * output_grad->matrix()
            ));
        }
        if (t2->computeGrad){
            t2_grad = make_tensor<T>(static_cast<DMatrix<T>>(
                // TODO:  Check to see if order is correct
                output_grad->matrix() * t3->matrix().transpose()
            ));
        }
        if (t1->computeGrad){
            t1_grad = make_tensor<T>(static_cast<DMatrix<T>>(
                output_grad->matrix().colwise().sum().transpose()
            ));
        }

#ifdef DEBUG
        if (t1->computeGrad){
            cout << "    t1_grad: " << t1_grad->rows() << ", " << t1_grad->cols() << endl;
        }
        if (t2->computeGrad){
            cout << "    t2_grad: " << t2_grad->rows() << ", " << t2_grad->cols() << endl;
        }
        if (t3->computeGrad){
            cout << "    t3_grad: " << t3_grad->rows() << ", " << t3_grad->cols() << endl;
        }
#endif

        return {t1_grad, t2_grad, t3_grad};
    }

    /*
        Returns t1+(t2*t3)
     */
    template<typename T>
    tensor<T> addmatmul(tensor<T> t1, tensor<T> t2, tensor<T> t3){
#ifdef DEBUG
        using namespace std;
        cout << "Tensor Add Matrix Multiply Forward:" << endl;
        cout << "    t1: "; print(cout, t1->shape()) << endl;
        cout << "    t2: "; print(cout, t2->shape()) << endl;
        cout << "    t3: "; print(cout, t3->shape()) << endl;
#endif
        auto t = make_tensor<T>(static_cast<DMatrix<T>>(
            (t2->matrix() * t3->matrix()).rowwise() + t1->matrix().transpose().row(0)
        ), t1->computeGrad || t2->computeGrad || t3->computeGrad);

        if (t->computeGrad){
            t->initGraph({t1, t2, t3}, addmatmul_backwards<T>);
        }

        return t;
    }

    /*
        Returns t1+(t2*t3)
     */
    template<typename T>
    tensor<T> addMultiply(tensor<T> t1, tensor<T> t2, tensor<T> t3){
        // TODO: Make this more general, i.e. Eigen::Tensor Contractions
        return addmatmul(t1, t2, t3);
    }

}

#endif // __CML_FUNCTIONS_TENSOROPS_TENSORADDMULTIPLY_H__
