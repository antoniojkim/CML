
#include <memory>

using namespace std;

class A;

shared_ptr<A> make_a(const int& t);

class A: public std::enable_shared_from_this<A> {
    int t;

    protected:

    A(const int& t): t{t} {}

    public:

    friend shared_ptr<A> make_a(const int& t){
        struct concrete_A: public A {};
        return make_shared
    }
};

shared_ptr<A> make_a(const int& t){
    return make_shared<A>(t);
}

class B: public std::enable_shared_from_this<B> {
    int t;

    protected:

    B(const int& t): t{t} {}

    public:

    friend shared_ptr<B> make_shared<B>(const int& t);

    static shared_ptr<B> make_b(const int& t){
        return make_shared<B>(t);
    }
};

int main(){

    auto a = make_a(3);
    auto b = B::make_b(3);

}
