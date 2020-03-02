
#include <cassert>

#include <Eigen/Core>

#include "../array.h"
#include "../array_attributes.h"
#include "../dtypes.h"
#include "../exception.h"
#include "../utils.h"

using namespace std;
using namespace numeric;

template<typename T>
using MatrixType = Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>;
template<typename T>
using DMatrix = Eigen::Map<MatrixType<T>>;
template<typename T>
using CMatrix = Eigen::Map<const MatrixType<T>>;

template<typename T>
Array<T> Array<T>::dot(const Array<T>& other) const {
    Array<T> out (vector<size_t>{this->rows(), other.cols()});
    dot(other, out);
    return out;
}

template<typename T>
void Array<T>::dot(const Array<T>& other, Array<T>& out) const {
#ifndef NO_ERROR_CHECKING
    if (this->ndim() != 2){
        throw numeric::Exception("Array::dot requires a1 be a 2-dimensional array. Got: ", this->ndim());
    }
    if (other.ndim() != 2){
        throw numeric::Exception("Array::dot requires a2 be a 2-dimensional array. Got: ", other.ndim());
    }
    if (out.ndim() != 2){
        throw numeric::Exception("Array::dot requires out be a 2-dimensional array. Got: ", out.ndim());
    }
    if (this->cols() != other.rows()){
        throw numeric::Exception("Array::dot received invalid shapes. Expected MxN and NxP arrays. ",
                                 "Got: ", this->rows(), "x", this->cols(), " and ", other.rows(), "x", other.cols());
    }
    if (out.rows() != this->rows() || out.cols() != other.cols()){
        throw numeric::Exception("Array::dot.out has invalid shape. ",
                                 "Expected: ", this->rows(), "x", other.cols(),
                                 "  Got: ", out.rows(), "x", out.cols());
    }
#endif

    // DMatrix<T> m1((T*) this->data().get(), Eigen::Index(this->rows()), Eigen::Index(this->cols()));
    DMatrix<T> m1 ((T*) this->data().get(), this->rows(), this->cols());
    DMatrix<T> m2 ((T*) other.data().get(), other.rows(), other.cols());
    DMatrix<T> mout ((T*) out.data().get(), out.rows(),   out.cols());

    // cout << "m1.shape:   " << (int) m1.rows() << "x" << (int) m1.cols() << "       " << this->rows() << ", " << this->cols() << endl;
    // cout << "m2.shape:   " << (int) m2.rows() << "x" << (int) m2.cols() << "       " << other.rows() << ", " << other.cols() << endl;
    // cout << "mout.shape: " << (int) mout.rows() << "x" << (int) mout.cols() << "       " << out.rows() << ", " << out.cols() << endl;

    mout.noalias() = m1 * m2;
}

template<typename T>
Array<T> Array<T>::zero() const {
    Array<T> out;
    *out.a = this->a.ero();

    if (out.size() != this->size()){
        throw numeric::Exception("Array::zero produces different size results: ", this->size(), " != ", out.size());
    }

    return out;
}


#define PREFIX
#define SELECT(T, _2)                                                       \
    template Array<T> Array<T>::dot(const Array<T>&) const;                 \
    template void Array<T>::dot(const Array<T>&, Array<T>& out) const;
#define SUFFIX

ARRAY_TYPES(PREFIX, SELECT, SUFFIX)
COMPLEX_TYPES(PREFIX, SELECT, SUFFIX)

#undef PREFIX
#undef SELECT
#undef SUFFIX
